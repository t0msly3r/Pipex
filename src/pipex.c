/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiz-ben <tfiz-ben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:33:38 by tfiz-ben          #+#    #+#             */
/*   Updated: 2025/04/30 15:35:58 by tfiz-ben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_free_split(char **split)
{
	int i = 0;

	if (!split)
		return;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

char *get_path(char **envp, char *cmd)
{
	char	**paths;
	char	*tmp;
	char	*full_path;
	int		i = 0;

	while (envp[i] && !ft_strnstr(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full_path, X_OK) == 0)
		{
			ft_free_split(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	ft_free_split(paths);
	return (NULL);
}

void	exec(char *argv, char **envp)
{
	char	*full_path;
	char	**tmp;
	
	tmp = ft_split(argv, ' ');
	if (!tmp)
	{
		perror("ft_split");
		exit(EXIT_FAILURE);
	}
	full_path = get_path(envp, tmp[0]);
	if (!full_path)
	{
		perror("get_path");
		ft_free_split(tmp);
		exit(EXIT_FAILURE);
	}
	if (execve(full_path, tmp, envp) == -1)
	{
		perror("execve");
		ft_free_split(tmp);
		exit(EXIT_FAILURE);
	}
}

void	child_process(int *pipefd, char **argv, char **envp)
{
	int		infile_fd;

	infile_fd = open(argv[1], O_RDONLY);
	if (infile_fd == -1)
	{
		perror("open");
		close(pipefd[0]);
		close(pipefd[1]);
		exit(EXIT_FAILURE);
	}
	dup2(infile_fd, STDIN_FILENO); // Redirect stdin to file
	dup2(pipefd[1], STDOUT_FILENO); // Redirect stdout to pipe write end
	close(infile_fd);
	close(pipefd[0]); // Close unused read end
	close(pipefd[1]); // Close write end after duplicating
	exec(argv[2], envp); // Execute command
}

void	father_process(int *pipefd, char **argv, char **envp)
{
	int		outfile_fd;

	outfile_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile_fd == -1)
	{
		perror("open");
		close(pipefd[0]);
		close(pipefd[1]);
		exit(EXIT_FAILURE);
	}
	dup2(pipefd[0], STDIN_FILENO); // Redirect stdin to pipe read end
	dup2(outfile_fd, STDOUT_FILENO); // Redirect stdout to file
	close(outfile_fd);
	close(pipefd[0]); // Close read end after duplicating
	close(pipefd[1]); // Close unused write end
	exec(argv[3], envp); // Execute command
}

int main(int argc, char **argv, char **envp)
{
	if (argc != 5)
	{
		fprintf(stderr, "Usage: %s <infile> <cmd1> <cmd2> <outfile>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	int		pipefd[2]; // Pipe file descriptors
	pid_t	pid; // Process ID

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork(); // Create a new process
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		child_process(pipefd, argv, envp); // Child process
	close(pipefd[1]); // Close write end in parent
	waitpid(pid, NULL, 0); // Wait for child process to finish
	father_process(pipefd, argv, envp); // Parent process
	close(pipefd[0]); // Close read end in parent
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiz-ben <tfiz-ben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:33:38 by tfiz-ben          #+#    #+#             */
/*   Updated: 2025/05/19 15:34:25 by tfiz-ben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

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

static void	child_process(int *pipefd, char **argv, char **envp)
{
	int	infile_fd;

	infile_fd = open(argv[1], O_RDONLY);
	if (infile_fd == -1)
	{
		perror("open");
		close(pipefd[0]);
		close(pipefd[1]);
		exit(EXIT_FAILURE);
	}
	dup2(infile_fd, STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	close(infile_fd);
	close(pipefd[0]);
	close(pipefd[1]);
	exec(argv[2], envp);
}

static void	father_process(int *pipefd, char **argv, char **envp)
{
	int	outfile_fd;

	outfile_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile_fd == -1)
	{
		perror("open");
		close(pipefd[0]);
		close(pipefd[1]);
		exit(EXIT_FAILURE);
	}
	dup2(pipefd[0], STDIN_FILENO);
	dup2(outfile_fd, STDOUT_FILENO);
	close(outfile_fd);
	close(pipefd[0]);
	close(pipefd[1]);
	exec(argv[3], envp);
}

int	main(int argc, char **argv, char **envp)
{
	int		pipefd[2];
	pid_t	pid;

	// if (argc != 5)
	// {
	// 	ft_putstr_fd("Usage: ./pipex infile cmd1 cmd2 outfile\n", 2);
	// 	exit(EXIT_FAILURE);
	// }
	if (check_error(argc, argv, envp))
	{
		if (pipe(pipefd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			close(pipefd[0]);
			close(pipefd[1]);
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
			child_process(pipefd, argv, envp);
		waitpid(pid, NULL, 0);
		father_process(pipefd, argv, envp);
	}
	else
		create_doc(argv);
	
}

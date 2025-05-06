/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiz-ben <tfiz-ben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:33:38 by tfiz-ben          #+#    #+#             */
/*   Updated: 2025/05/05 12:54:57 by tfiz-ben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

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
    int     pipefd[2];
    pid_t   pid;

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
        process_first_command(pipefd, argv, envp);
    waitpid(pid, NULL, 0);
    process_second_command(pipefd, argv, envp);
}
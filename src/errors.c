/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiz-ben <tfiz-ben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:54:51 by tfiz-ben          #+#    #+#             */
/*   Updated: 2025/05/19 16:03:28 by tfiz-ben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	create_doc(char **argv)
{
	int	outfile_fd;

	outfile_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile_fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
}

void	*check_cmd(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	char	*env_path;

	env_path = find_env_path(envp);
	if (!env_path)
	{
		free(cmd);
		return (NULL);
	}
	paths = ft_split(env_path, ':');
	if (!paths)
	{
		free(env_path);
		free(cmd);
		return (NULL);
	}
	path = check_paths(paths, cmd);
	ft_free_split(paths);
	free(cmd);
	if (!path)
		return (NULL);
	free(path);
	return (" ");
}

char	*get_cmd(char *argv)
{
	char	**cmd;
	char *res;
	
	cmd = ft_split(argv, ' ');
	if (!cmd)
	{
		perror("ft_split");
		exit(EXIT_FAILURE);
	}
	res = ft_strdup(cmd[0]);
	ft_free_split(cmd);
	return (res);
}

void	*check_error(int argc, char **argv, char **envp)
{
	char	*cmd;

	cmd = get_cmd(argv[3]);
	if (!cmd)
	{
		ft_putstr_fd("Error: Command not found\n", 2);
		exit(EXIT_FAILURE);
	}
	if (argc != 5)
	{
		ft_putstr_fd("Usage: ./pipex infile cmd1 cmd2 outfile\n", 2);
		exit(EXIT_FAILURE);
	}
	if (!envp)
	{
		ft_putstr_fd("Error: Environment variables not found\n", 2);
		exit(EXIT_FAILURE);
	}
	if (!check_cmd(cmd, envp))
	{
		return (NULL);
	}
	return (" ");
}

// void	check_arguments(char **argv)
// {
// 	int	i;

// 	i = 0;
// 	if (argv[1] == NULL || argv[2] == NULL || argv[3] == NULL || argv[4] == NULL)
// 	{
// 		ft_putstr_fd("Error: Invalid arguments\n", 2);
// 		exit(EXIT_FAILURE);
// 	}
// }
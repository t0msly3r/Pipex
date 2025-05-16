/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiz-ben <tfiz-ben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:54:51 by tfiz-ben          #+#    #+#             */
/*   Updated: 2025/05/16 13:56:26 by tfiz-ben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	check_cmd(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	char	*env_path;

	env_path = find_env_path(envp);
	if (!env_path)
	{
		ft_putstr_fd("Error: PATH not found in environment\n", 2);
		exit(EXIT_FAILURE);
	}
	paths = ft_split(env_path, ':');
	path = check_paths(paths, cmd);
	if (!path)
	{
		ft_putstr_fd("Error: Command not found\n", 2);
		ft_free_split(paths);
		exit(EXIT_FAILURE);
	}
	free(path);
	ft_free_split(paths);
}

void	check_error(int argc, char **argv, char **envp)
{
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
	check_cmd(argv[3], envp);
}

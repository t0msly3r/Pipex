/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiz-ben <tfiz-ben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:07:31 by tfiz-ben          #+#    #+#             */
/*   Updated: 2025/04/30 15:16:23 by tfiz-ben         ###   ########.fr       */
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

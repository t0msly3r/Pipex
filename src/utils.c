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

char *find_env_path(char **envp)
{
	int i = 0;
	
	while (envp[i] && !ft_strnstr(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		return (NULL);
	return (envp[i] + 5);
}

char *build_full_path(char *dir, char *cmd)
{
	char *tmp;
	char *full_path;
	
	tmp = ft_strjoin(dir, "/");
	full_path = ft_strjoin(tmp, cmd);
	free(tmp);
	return (full_path);
}

char *check_paths(char **paths, char *cmd)
{
	int i = -1;
	char *full_path;
	
	while (paths[++i])
	{
		full_path = build_full_path(paths[i], cmd);
		if (!full_path)
			return (NULL);
		if (access(full_path, X_OK) == 0)
		{
			ft_free_split(paths);
			return (full_path);
		}
		free(full_path);
	}
	return (NULL);
}

char *get_path(char **envp, char *cmd)
{
	char **paths;
	char *env_path;
	char *result;
	
	env_path = find_env_path(envp);
	if (!env_path)
		return (NULL);
	paths = ft_split(env_path, ':');
	if (!paths)
		return (NULL);
	result = check_paths(paths, cmd);
	if (!result)
		ft_free_split(paths);
	return (result);
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

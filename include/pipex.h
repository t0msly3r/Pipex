/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiz-ben <tfiz-ben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:27:41 by tfiz-ben          #+#    #+#             */
/*   Updated: 2025/05/19 15:33:43 by tfiz-ben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include "../lib/libft.h"
# include <fcntl.h>

void	exec(char *argv, char **envp);
char	*get_path(char **envp, char *cmd);
void	ft_free_split(char **split);
char	*check_paths(char **paths, char *cmd);
char	*check_paths(char **paths, char *cmd);
char	*find_env_path(char **envp);
char	*build_full_path(char *dir, char *cmd);
void	*check_error(int argc, char **argv, char **envp);
void	*check_cmd(char *cmd, char **envp);
void	create_doc(char **argv);

#endif

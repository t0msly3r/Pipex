#ifndef PIPEX_H
# define PIPEX_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include "../lib/libft.h"
#include <fcntl.h>

void	exec(char *argv, char **envp);
char	*get_path(char **envp, char *cmd);
void	ft_free_split(char **split);

#endif

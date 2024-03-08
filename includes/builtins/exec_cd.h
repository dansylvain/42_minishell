#ifndef EXEC_CD_H
#define EXEC_CD_H

#include <minishell_struct.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <libft.h>

void	update_home_env_var(t_Data *data);
int	exec_cd(t_Data *data, char **command_tab);
void	add_env_var_to_envp_tab(char **command_tab, t_Data *data, int *i);
void	display_error(char *str);
void	display_error_detail(char *str, char *details, char *str2);

#endif

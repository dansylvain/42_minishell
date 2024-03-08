#ifndef EXEC_ENV_H
#define EXEC_ENV_H

#include <minishell_struct.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "ft_printf.h"

void	exec_env(t_Data *data, char **command_tab);
void	display_error_detail(char *str, char *details, char *str2);

#endif

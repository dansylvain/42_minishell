#ifndef EXEC_ECHO_H
#define EXEC_ECHO_H

#include <minishell_struct.h>
#include "ft_printf.h"
#include "libft.h"

void	exec_echo(t_Data *data, char **command_tab);
int	is_only_space(char *str);
int	is_not_empty_prompt(char *str);

#endif

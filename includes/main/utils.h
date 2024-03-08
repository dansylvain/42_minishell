#ifndef UTILS_H
#define UTILS_H

#include "minishell_struct.h"
#include "parsing_utils.h"
#include <stdlib.h>
#include "ft_printf.h"
#include "libft.h"

void	close_minishell(t_Data *data);
void	free_data(t_Data *data);
void	free_command_tab(char ***command_tab);
void	free_command_tab_lg(char ***command_tab);

#endif

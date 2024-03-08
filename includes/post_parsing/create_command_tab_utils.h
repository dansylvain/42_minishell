#ifndef CREATE_COMMAND_TAB_UTILS_H
#define CREATE_COMMAND_TAB_UTILS_H

#include <minishell_struct.h>
#include "parsing_utils.h"
#include <stddef.h>
#include "libft.h"
#include "ft_printf.h"

int	is_separator(t_ast_nde *node);
int	is_chevron(t_ast_nde *node);
int	is_pipeline(t_ast_nde *cmd_tab_node_sav);
int	get_cmd_nbr(t_ast_nde *node);
void	display_command_tab(char **command_tab);
void	display_command_tab_big(char ***command_tab);

#endif

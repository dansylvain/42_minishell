#ifndef EXEC_EXPORT_UTILS_2_H
#define EXEC_EXPORT_UTILS_2_H

#include <minishell_struct.h>
#include <stddef.h>
#include "libft.h"
#include "parsing_utils.h"

int	are_only_valid_chars(char *str);
void	store_and_free_cmd_tab_node_sav(t_ast_nde *cmd_tab_node_sav);;

#endif

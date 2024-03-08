#ifndef EXEC_EXIT_H
#define EXEC_EXIT_H

#include <minishell_struct.h>
#include <stdlib.h>
#include "ft_printf.h"
#include "libft.h"
#include "parsing_utils.h"


void	store_and_free_cmd_list(t_ast_nde *cmd_list);;
void	store_and_free_cmd_tab_node_sav(t_ast_nde *cmd_tab_node_sav);;
void	store_and_free_cmd_tab(char ***cmd_tab);;
void	display_exit_stuff(t_Data *data, char **command_tab);
int	exec_exit(t_Data *data, char **command_tab);
int	str_is_digit(char *str);
void	display_error_detail(char *str, char *details, char *str2);
void	display_error(char *str);
void	free_data(t_Data *data);

#endif

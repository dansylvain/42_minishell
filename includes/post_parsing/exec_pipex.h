#ifndef EXEC_PIPEX_H
#define EXEC_PIPEX_H

#include <minishell_struct.h>
#include "parsing_utils.h"
#include <stddef.h>

void	exec_pipex(t_Data *data, char *cmd, char *envp[]);
void	store_and_free_cmd_list(t_ast_nde *cmd_list);
t_ast_nde	*parse(char *str, t_Data *data);
void		launch_command_tab(t_Data *data, t_ast_nde *node,
void	store_and_free_cmd_list(t_ast_nde *cmd_list);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command_tab.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 12:43:46 by dan               #+#    #+#             */
/*   Updated: 2024/03/12 14:13:32 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "create_command_tab.h"
#include "ft_printf.h"
int		is_separator(t_ast_nde *node);
int		is_chevron(t_ast_nde *node);
void	display_command_tab_big(char ***command_tab);
void	print_node(t_ast_nde *node);
void	print_tree(t_ast_nde *node);

int	get_pipe_parts_nbr(t_ast_nde *node);
char ***alloc_memory_for_pipe_parts(char ***cmd_tab, int pipe_parts_nbr);
int	get_pipe_elements_nbr(t_ast_nde *node);
char **alloc_memory_for_pipe_elements(char **cmd_tab, int pipe_elements_nbr);



/**========================================================================
 *                           store_and_free_cmd_tab
 *========================================================================**/
void	store_and_free_cmd_tab(char ***cmd_tab)
{
	static char	***cmd_tab_lcl;

	if (cmd_tab)
		cmd_tab_lcl = cmd_tab;
	else
		free_command_tab_lg(cmd_tab_lcl);
}


char	**add_redirections(char **cmd_tab, t_ast_nde *node)
{
	return (cmd_tab);
}
/**========================================================================
 *                           create_command_tab
 *========================================================================**/
char	***create_command_tab(t_Data *data, t_ast_nde *node, char *envp[])
{
	char ***cmd_tab;
	int	pipe_parts_nbr;
	int	pipe_elements_nbr;
	
	// compter le combre de bloc de commandes + alloc
		// compter le nombre de ss-blocs de commandes + alloc
			// insertion redirections
			// insertions commands + flags
		// insertion du séparateur
	
	// check_pipeline_validity();
	pipe_parts_nbr = get_pipe_parts_nbr(node);
	cmd_tab = alloc_memory_for_pipe_parts(cmd_tab, pipe_parts_nbr);
	pipe_elements_nbr = get_pipe_elements_nbr(node);
	cmd_tab[0] = alloc_memory_for_pipe_elements(cmd_tab[0], pipe_elements_nbr);
	cmd_tab[0] = add_redirections(cmd_tab[0], node); // malloc included
	ft_printf("pipe_elements_nbr: %i\n", pipe_elements_nbr);
	ft_printf("pipe_parts_nbr: %i\n", pipe_parts_nbr);	
	/* add_remaining_cmds(); // malloc included
	insert_separator(); // malloc included */
	
	
	
	
	
	display_command_tab_big(cmd_tab);
	free_command_tab_lg(cmd_tab);

	return (cmd_tab);
}

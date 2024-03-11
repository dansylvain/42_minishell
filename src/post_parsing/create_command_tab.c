/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command_tab.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 12:43:46 by dan               #+#    #+#             */
/*   Updated: 2024/03/11 09:57:49 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "create_command_tab.h"
#include "ft_printf.h"
int		is_separator(t_ast_nde *node);
int		is_chevron(t_ast_nde *node);
void	display_command_tab_big(char ***command_tab);
void	print_node(t_ast_nde *node);
void	print_tree(t_ast_nde *node);



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

int	get_pipe_parts_nbr(t_ast_nde *node)
{
	int pipe_parts_nbr;
	
	pipe_parts_nbr = 1;
	while (node)
	{
		if (is_separator(node))
			pipe_parts_nbr++;
		node = node->sibling;
	}
	return (pipe_parts_nbr);
}

char ***alloc_memory_for_pipe_parts(char ***cmd_tab, int pipe_parts_nbr)
{
	cmd_tab = ft_calloc(pipe_parts_nbr + 1, sizeof(char **));
	if (cmd_tab == NULL)
	{
		ft_printf("alloc cmd_tab first level failed\n");
		return (NULL);
	}
	cmd_tab[pipe_parts_nbr] = NULL;
	return (cmd_tab);
}

int	get_pipe_elements_nbr(t_ast_nde *node)
{
	int	pipe_elements_nbr;

	pipe_elements_nbr = 0;
	while (!is_separator(node))
	{
		if (is_chevron(node->child))
			pipe_elements_nbr--;
		pipe_elements_nbr++;
		node = node->sibling;
	}
	return (pipe_elements_nbr);
}

char **alloc_memory_for_pipe_elements(char **cmd_tab, int pipe_elements_nbr)
{
	cmd_tab = ft_calloc(pipe_elements_nbr + 1, sizeof(char *));
	if (cmd_tab == NULL)
	{
		ft_printf("alloc cmd_tab second level failed\n");
		return (NULL);
	}
	cmd_tab[pipe_elements_nbr] = NULL;
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
	/* add_redirections(); // malloc included
	add_remaining_cmds(); // malloc included
	insert_separator(); // malloc included */
	
	
	
	
	
	display_command_tab_big(cmd_tab);
	free_command_tab_lg(cmd_tab);

	return (cmd_tab);
}

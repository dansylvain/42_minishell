/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command_tab_allocation.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:43:56 by dan               #+#    #+#             */
/*   Updated: 2024/03/13 07:47:31 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_utils.h"
#include "minishell.h"
#include "libft.h"
#include "ft_printf.h"

int		is_separator(t_ast_nde *node);
int		is_chevron(t_ast_nde *node);
void	display_command_tab_big(char ***command_tab);
void	print_node(t_ast_nde *node);
void	print_tree(t_ast_nde *node);
char	*get_node_str(t_ast_nde *node);
int		get_pipe_parts_nbr(t_ast_nde **node);
char	***alloc_memory_for_pipe_parts(char ***cmd_tab, int pipe_parts_nbr);
int		get_pipe_elements_nbr(t_ast_nde *node);
char	**alloc_memory_for_pipe_elements(char **cmd_tab, int pipe_elements_nbr);

/**========================================================================
 *                           get_pipe_parts_nbr
 *! FUNC DOES NOT COUNT RIGHT ELEMENTS 
 *========================================================================**/
int	get_pipe_parts_nbr(t_ast_nde **node)
{
	t_ast_nde	*start;
	int			pipe_parts_nbr;
	int			cmd_was_counted;

	cmd_was_counted = 0;
	pipe_parts_nbr = 0;
	start = *node;
	while (*node)
	{
		if (!is_chevron(*node) && !cmd_was_counted++)
		{
			pipe_parts_nbr += 1;
			cmd_was_counted++;
		}
		if (is_separator(*node))
		{
			pipe_parts_nbr += 1;
			cmd_was_counted = 0;
		}
		if (is_chevron(*node))
			pipe_parts_nbr += 1;
		*node = (*node)->sibling;
	}
	(*node) = start;
	return (pipe_parts_nbr);
}

/**========================================================================
 *                           alloc_memory_for_pipe_parts
 *========================================================================**/
char	***alloc_memory_for_pipe_parts(char ***cmd_tab, int pipe_parts_nbr)
{
	cmd_tab = ft_calloc(pipe_parts_nbr + 1, sizeof(char **));
	if (cmd_tab == NULL)
	{
		return (NULL);
	}
	cmd_tab[pipe_parts_nbr] = NULL;
	return (cmd_tab);
}

/**========================================================================
 *                           get_cmd_nbr
 *========================================================================**/
int	get_cmd_nbr(t_ast_nde *node)
{
	int	nbr;

	nbr = 0;
	while (!is_separator(node))
	{
		if (!is_chevron(node->child) && node->token != CMD)
			nbr++;
		node = node->sibling;
	}
	return (nbr);
}

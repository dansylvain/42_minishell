/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command_tab_allocation.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:43:56 by dan               #+#    #+#             */
/*   Updated: 2024/03/12 14:11:46 by dan              ###   ########.fr       */
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

int	get_pipe_parts_nbr(t_ast_nde *node);
char ***alloc_memory_for_pipe_parts(char ***cmd_tab, int pipe_parts_nbr);
int	get_pipe_elements_nbr(t_ast_nde *node);
char **alloc_memory_for_pipe_elements(char **cmd_tab, int pipe_elements_nbr);


int	get_pipe_parts_nbr(t_ast_nde *node)
{
	int pipe_parts_nbr;
	
	pipe_parts_nbr = 1;
	while (node)
	{
		if (is_separator(node))
			pipe_parts_nbr += 2;
		node = node->sibling;
	}
	return (pipe_parts_nbr);
}

char ***alloc_memory_for_pipe_parts(char ***cmd_tab, int pipe_parts_nbr)
{
	cmd_tab = ft_calloc(pipe_parts_nbr + 1, sizeof(char **));
	if (cmd_tab == NULL)
	{
		return (NULL);
	}
	cmd_tab[pipe_parts_nbr] = NULL;
	return (cmd_tab);
}

int	get_pipe_elements_nbr(t_ast_nde *node)
{
	int	pipe_elements_nbr;
	int	cmd_was_added;

	pipe_elements_nbr = 0;
	cmd_was_added = 0;
	if (is_separator(node))
		return (1);
	while (!is_separator(node))
	{
		if (!is_chevron(node->child) && !cmd_was_added++)
			pipe_elements_nbr++;
		if (is_chevron(node->child))
		{
			pipe_elements_nbr++;
			node = node->sibling;
		}
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

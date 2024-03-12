/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command_tab_allocation.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:43:56 by dan               #+#    #+#             */
/*   Updated: 2024/03/12 22:27:33 by dan              ###   ########.fr       */
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
char	*get_node_str(t_ast_nde *node);;

int	get_pipe_parts_nbr(t_ast_nde **node);
char ***alloc_memory_for_pipe_parts(char ***cmd_tab, int pipe_parts_nbr);
int	get_pipe_elements_nbr(t_ast_nde *node);
char **alloc_memory_for_pipe_elements(char **cmd_tab, int pipe_elements_nbr);



//! FUNC DOES NOT COUNT RIGHT ELEMENTS
int	get_pipe_parts_nbr(t_ast_nde **node)
{
	t_ast_nde *start;
	int pipe_parts_nbr;
	int	cmd_was_counted;
	
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
	// ft_printf("pipe_parts_nbr: %i\n", pipe_parts_nbr);
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

// int	get_pipe_elements_nbr(t_ast_nde *node)
// {
// 	int	pipe_elements_nbr;
// 	int	cmd_was_added;

// 	pipe_elements_nbr = 0;
// 	cmd_was_added = 0;
// 	if (is_separator(node))
// 		return (1);
// 	while (!is_separator(node))
// 	{
// 		if (!is_chevron(node->child) && !cmd_was_added++)
// 			pipe_elements_nbr++;
// 		if (is_chevron(node->child))
// 		{
// 			pipe_elements_nbr++;
// 			node = node->sibling;
// 		}
// 		node = node->sibling;
// 	}
// 	return (pipe_elements_nbr);
// }

// char **alloc_memory_for_pipe_elements(char **cmd_tab, int pipe_elements_nbr)
// {
// 	cmd_tab = ft_calloc(pipe_elements_nbr + 1, sizeof(char *));
// 	if (cmd_tab == NULL)
// 	{
// 		ft_printf("alloc cmd_tab second level failed\n");
// 		return (NULL);
// 	}
// 	cmd_tab[pipe_elements_nbr] = NULL;
// 	return (cmd_tab);
// }
char	**add_sep_tab(char **cmd_tab_sep, t_ast_nde *node)
{
	char *sep;

	if (node->token == PIPE)
		sep = "|";
	if (node->token == AND)
		sep = "&&";
	if (node->token == OR)
		sep = "||";
	cmd_tab_sep = ft_calloc(2, sizeof(char *));
	cmd_tab_sep[0] = ft_strdup(sep);
	cmd_tab_sep[1] = NULL;
	// ft_printf("alloc for cmd_tab_sep\nsep: %s\n%s\n", sep, cmd_tab_sep[0]);
	return (cmd_tab_sep);
}

char ***add_redir_tabs(char ***cmd_tab, t_ast_nde **node, int *i)
{
	char *chev;
	
	if ((*node)->token == SCHEV_LFT)
		chev = "<";
	if ((*node)->token == SCHEV_RGTH)
		chev = ">";
	if ((*node)->token == DCHEV_LFT)
		chev = "<<";
	if ((*node)->token == DCHEV_RGTH)
		chev = ">>";
	cmd_tab[*i] = ft_calloc(3, sizeof(char *));
	cmd_tab[*i][0] = ft_strdup(chev);
	cmd_tab[*i][1] = get_node_str((*node)->sibling->child);
	cmd_tab[*i][2] = NULL;
	(*node)->sibling->token = CMD;
	(*i)++;
	return (cmd_tab);
}

int	get_cmd_nbr(t_ast_nde *node)
{
	int	nbr;
	
	nbr = 0;
	while(!is_separator(node))
	{
		if (!is_chevron(node->child) && node->token != CMD)
			nbr++;
		node = node->sibling;
	}
	// ft_printf("get_cmd_nbr: %i\n", nbr);
	return (nbr);
}

char **add_remaining_tabs(char **cmd_tab_tab, t_ast_nde *node)
{
	int	nbr;
	int i;
	
	nbr = get_cmd_nbr(node);
	cmd_tab_tab = ft_calloc(nbr + 1, sizeof(char *));
	cmd_tab_tab[nbr] = NULL;
	i = 0;
	while (!is_separator(node))
	{
		if (!is_chevron(node) && node->token != CMD)
			cmd_tab_tab[i++] = get_node_str(node->child);
		node = node->sibling;
	}

	return (cmd_tab_tab);
}

char	***alloc_memory_for_tab_tabs(char ***cmd_tab, t_ast_nde *node)
{
	int	pipe_elements_nbr;
	t_ast_nde *current;
	t_ast_nde *start;
	int	i;
	int	redir_were_added;
	int	cmd_was_added;
	
	cmd_was_added = 0;
	redir_were_added = 0;
	i = 0;
	start = node;
	while (node)
	{
		if (node == start || is_separator(node))
		{
			// ft_printf("reset flags %i\n", i);
			if (is_separator(node))
			{
				cmd_tab[i] = add_sep_tab(cmd_tab[i], node);
				// ft_printf("%s\n", cmd_tab[i][0]);
				node = node->sibling;
				i++;
			}
			redir_were_added = 0;
			cmd_was_added = 0;
		}
		if (redir_were_added == 0)
		{
			current = node;
			while (!is_separator(current))
			{
				if (is_chevron(current))
				{
					cmd_tab = add_redir_tabs(cmd_tab, &current, &i);
				}
				current = current->sibling;
			}
			redir_were_added = 1;
		}
		// ft_printf("i: %i\n", i);
		if (cmd_was_added == 0)
		{
			cmd_tab[i] = add_remaining_tabs(cmd_tab[i], node);
			cmd_was_added = 1;
			i++;
		}
		
			
		node = node->sibling;
	}
	
	return (cmd_tab);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command_tab.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 12:43:46 by dan               #+#    #+#             */
/*   Updated: 2024/02/08 12:43:59 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "parsing_utils.h"

int			pipex(char *argv[], char *envp[]);

void	display_command_tab(char **command_tab)
{
	int	i;

	i = 0;
	ft_printf("command_tab: \n");
	while (command_tab[i])
	{
		ft_printf("commands_tab[%i]: >%s<\n", i, command_tab[i]);
		i++;
	}
}

void	get_command_nbr(t_ast_nde **current, int *tree_length)
{
	(*tree_length) = 0;
	while (*current)
	{
		if ((*current)->token == AND || (*current)->token == OR)
			break ;
		if ((*current)->token != PIPE && (*current)->end
			- (*current)->start + 1)
			(*tree_length)++;
		*current = (*current)->sibling;
	}
}

char	**fill_command_tab(char ***commands_tab,
	t_ast_nde **node, int return_pipex)
{
	int	i;

	i = 0;
	if (return_pipex && (*node)->sibling->sibling)
		(*node) = (*node)->sibling->sibling;
	while (*node)
	{
		if ((*node)->token == AND || (*node)->token == OR)
			break ;
		if ((*node)->token != PIPE && (*node)->end - (*node)->start + 1)
		{
			(*commands_tab)[i] = ft_strndup((*node)->start,
					(*node)->end - (*node)->start + 1);
			if ((*commands_tab)[i] == NULL)
				return (NULL);
			i++;
		}
		(*node) = (*node)->sibling;
	}
	(*commands_tab)[i] = NULL;
	return (*commands_tab);
}

char	**create_command_tab(t_ast_nde *node, char *envp[])
{
	char		**commands_tab;
	int			return_pipex;
	int			tree_length;
	t_ast_nde	*current;

	return_pipex = 0;
	while (node)
	{
		current = node;
		get_command_nbr(&current, &tree_length);
		commands_tab = (char **)malloc(sizeof(char *) * tree_length + 1);
		if (commands_tab == 0)
			return (NULL);
		commands_tab = fill_command_tab(&commands_tab, &node, return_pipex);
		display_command_tab(commands_tab);
		return_pipex = pipex(commands_tab, envp);
		if (node == NULL)
			break ;
		if (node->token == OR && return_pipex == 0)
			return_pipex = 1;
		if (node->token == OR && return_pipex == 1)
			return_pipex = 0;
		node = node->sibling;
		continue ;
	}
}

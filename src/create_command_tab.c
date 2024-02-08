/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command_tab.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 12:43:46 by dan               #+#    #+#             */
/*   Updated: 2024/02/08 17:41:53 by dan              ###   ########.fr       */
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

int	is_env_var(char *str)
{
	int	i;
	char tok[] = "\'\"<>|&";
	
	if (str[0] != '$')
		return (0);
	i = 0;
	while (tok[i] != '\0')
		if (str[1] == tok[i++])
			return (0);
	if (str[1] == '\0')
		return (0);
	return (1);
}

char *get_env_var(t_Data *data, char *str)
{
	int i;
	int j;
	char buff[2000];
	
	ft_bzero(buff, 2000);
	i = 0;
	while (str[i] && (str[i] != ' ' && str[i] != '\'' && str[i] != '\"' && str[i] != '>' && str[i] != '<' && str[i] != '|' && str[i] != '&'))
		i++;
	
	ft_printf("AFFICHAGE DE LA PUTAIN DE VARIABLE: ");
	int k = 0;
	while (k != i - 1)
	{
		buff[k] = str[k + 1];
		k++;
	}
	ft_printf("%s\n", buff);
	


	j = 0;
	while (data->envp_tab[j])
	{

		if (!ft_strncmp(buff, data->envp_tab[j], i - 1))
		{
			ft_printf("HOLLY COW!!!\n");
			ft_printf("buff: %s\n", buff);
			ft_printf("value: %s\n", getenv(buff));
		}
		j++;
	}
}

char	**fill_command_tab(t_Data *data, char ***commands_tab,
	t_ast_nde **node, int return_pipex)
{
	int			i;
	int			j;
	t_ast_nde	*current;

	// ignores first node if return_pipex is failure
	if (return_pipex && (*node)->sibling->sibling)
		(*node) = (*node)->sibling->sibling;
	
	i = 0;
	while (*node)
	{
		if ((*node)->token == AND || (*node)->token == OR)
			break ;
		current = (*node)->child; 
		while (current)
		{
			if (current->token == DQUTE || current->token == RAW)
			{
				j = 0;
				while (j < current->end - current->start + 1)
				{
					if (is_env_var(&current->start[j]))
					{
						ft_printf("ENV VAR: %s", &current->start[j]);
						get_env_var(data, &current->start[j]);
					}
						
					j++;
				}
			}
			current = current->sibling;
		}

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

char	**create_command_tab(t_Data *data, t_ast_nde *node, char *envp[])
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
		commands_tab = fill_command_tab(data, &commands_tab, &node, return_pipex);
		display_command_tab(commands_tab);
		return_pipex = pipex(commands_tab, envp);
		ft_printf("return_pipex: %i\n", return_pipex);
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

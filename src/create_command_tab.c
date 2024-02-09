/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command_tab.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 12:43:46 by dan               #+#    #+#             */
/*   Updated: 2024/02/09 10:54:12 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "parsing_utils.h"

void	print_tree(t_ast_nde *node);

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

char *get_env_var(t_Data *data, char *str, char buff[])
{
	int i;
	int j;
	
	ft_bzero(buff, 2000);
	i = 0;
	while (str[i] && (str[i] != ' ' && str[i] != '\'' && str[i] != '\"' && str[i] != '>' && str[i] != '<' && str[i] != '|' && str[i] != '&'))
		i++;
	int k = 0;
	while (k != i)
	{
		buff[k] = str[k];
		k++;
	}
	j = 0;
	while (data->envp_tab[j])
	{
		if (!ft_strncmp(&buff[1], data->envp_tab[j], i - 1))
		{
			return (getenv(&buff[1]));
		}
		j++;
	}
}

void expand_env_var(char **command, char *env_var, char buff[])
{
	char	*start;
	char	*end;
	int		len;
	char	*sav_command;
	
	sav_command = (*command);
	len = ft_strlen(buff);
	start = ft_strstr((*command), buff);
	end = &start[len];
	(*command) = (char *)ft_calloc(ft_strlen(sav_command) - len + ft_strlen(env_var) + 1, sizeof(char));
	if ((*command) == NULL)
		return ;
	ft_strlcpy((*command), sav_command, &start[0] - &sav_command[0] + 1);
	ft_strlcat(&(*command)[ft_strlen((*command))], env_var, ft_strlen(env_var) + 1);
	ft_strlcat(&(*command)[ft_strlen((*command))], end, ft_strlen(end) + 1);
	free(sav_command);
}
char	**fill_command_tab(t_Data *data, char ***commands_tab,
	t_ast_nde **node, int return_pipex)
{
	int			i;
	int			j;
	t_ast_nde	*current;
	char 		*env_var;
	char		buff[2000];

	if (return_pipex && (*node)->sibling->sibling)
		(*node) = (*node)->sibling->sibling;
	i = 0;
	while (*node)
	{
		env_var = NULL;
		if ((*node)->token == AND || (*node)->token == OR)
			break ;
		current = (*node)->child; 
		while (current)
		{
			if (current->token == IN_DQUTE || current->token == RAW)
			{
				j = 0;
				while (j < current->end - current->start + 1)
				{
					if (is_env_var(&current->start[j]))
					{
						env_var = get_env_var(data, &current->start[j], buff);
					}
					j++;
				}
			}
			current = current->sibling;
		}

	/**========================================================================
	 *! verification to be removed! ((*node)->end - (*node)->start + 1))            
	 *========================================================================**/
		if ((*node)->token != PIPE && (*node)->end - (*node)->start + 1)
		{
			int k = 0;
			
			(*commands_tab)[i] = ft_strndup((*node)->start,
					(*node)->end - (*node)->start + 1);
			if ((*commands_tab)[i] == NULL)
				return (NULL);
			if ((*node)->child->token == RAW || (*node)->child->token == DQUTE)
			{
				if (env_var)
				{
					expand_env_var(&((*commands_tab)[i]), env_var, buff);
				}
			}
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command_tab.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 12:43:46 by dan               #+#    #+#             */
/*   Updated: 2024/02/10 17:46:19 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "parsing_utils.h"

void	print_tree(t_ast_nde *node);

int		pipex(char *argv[], char *envp[]);

void	display_command_tab(char **command_tab)
{
	int	i;

	i = 0;
	ft_printf("command_tab: \n");
	while (command_tab[i])
	{
		ft_printf("cmd_tab[%i]: >%s<\n", i, command_tab[i]);
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
	int		i;
	char	*tok;

	tok = "\'\"<>|&";
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

char	*get_env_var(t_Data *data, char *str, char buff[])
{
	int		i;
	int		j;
	int		k;
	char	*env_var;

	ft_bzero(buff, 2000);
	i = 0;
	while (str[i] && (str[i] != ' ' && str[i] != '\'' && str[i] != '\"'
			&& str[i] != '>' && str[i]
			!= '<' && str[i] != '|' && str[i] != '&'))
		i++;
	k = 0;
	ft_memcpy(buff, str, i);
	buff[i] = '\0';
	if (!ft_strcmp(buff, "$?"))
		return (ft_itoa(data->exit_status));
	j = 0;
	while (data->envp_tab[j])
	{
		if (!ft_strncmp(&buff[1], data->envp_tab[j], i - 1)
			&& data->envp_tab[j][ft_strlen(buff) - 1] == '=')
			return (getenv(&buff[1]));
		j++;
	}
	env_var = ft_strdup(buff);
	ft_bzero(env_var, ft_strlen(buff));
	return (env_var);
}

void	insert_env_var(char **command, char *env_var, char buff[])
{
	char	*start;
	char	*end;
	int		len;
	char	*sav_command;

	sav_command = (*command);
	len = ft_strlen(buff);
	start = ft_strstr((*command), buff);
	end = &start[len];
	(*command) = (char *)ft_calloc(ft_strlen(sav_command)
			- len + ft_strlen(env_var) + 1, sizeof(char));
	if ((*command) == NULL)
		return ;
	ft_strlcpy((*command), sav_command, &start[0] - &sav_command[0] + 1);
	ft_strlcat(&(*command)[ft_strlen((*command))],
		env_var, ft_strlen(env_var) + 1);
	ft_strlcat(&(*command)[ft_strlen((*command))], end, ft_strlen(end) + 1);
	free(sav_command);
}

void	check_if_env_var_and_get_it(t_Data *data, t_ast_nde **node, char **env_var, char buff[])
{
	t_ast_nde	*current;
	int	j;

	current = (*node)->child;
	while (current)
	{
		if (current->token == IN_DQUTE || current->token == RAW)
		{
			j = 0;
			while (j < current->end - current->start + 1)
			{
				if (is_env_var(&current->start[j]))
					*env_var = get_env_var(data, &current->start[j], buff);
				j++;
			}
		}
		current = current->sibling;
	}
}

char	**fill_command_tab(t_Data *data, char ***cmd_tab,
	t_ast_nde **node)
{
	int			i;
	char		*env_var;
	char		buff[2000];

	if (data->exit_status && (*node)->sibling->sibling)
		(*node) = (*node)->sibling->sibling;
	i = 0;
	while (*node)
	{
		if ((*node)->token == AND || (*node)->token == OR)
			break ;
		env_var = NULL;
		check_if_env_var_and_get_it(data, node, &env_var, buff);
		if ((*node)->token != PIPE && (*node)->end - (*node)->start + 1)
		{
			(*cmd_tab)[i] = ft_strndup((*node)->start,
					(*node)->end - (*node)->start + 1);
			if ((*cmd_tab)[i] == NULL)
				return (NULL);
			if ((*node)->child->token == RAW || (*node)->child->token == DQUTE)
				if (env_var)
					insert_env_var(&((*cmd_tab)[i]), env_var, buff);
			i++;
		}
		(*node) = (*node)->sibling;
	}
	(*cmd_tab)[i] = NULL;
	return (*cmd_tab);
}

char	**create_command_tab(t_Data *data, t_ast_nde *node, char *envp[])
{
	char		**cmd_tab;
	int			tree_length;
	t_ast_nde	*current;

	data->exit_status = 0;
	while (node)
	{
		current = node;
		get_command_nbr(&current, &tree_length);
		cmd_tab = (char **)malloc(sizeof(char *) * tree_length + 1);
		if (cmd_tab == 0)
			return (NULL);
		cmd_tab = fill_command_tab(data, &cmd_tab, &node);
		display_command_tab(cmd_tab);
		data->exit_status = pipex(cmd_tab, envp);
		if (node == NULL)
			break ;
		if (node->token == OR && data->exit_status == 0)
			data->exit_status = 1;
		if (node->token == OR && data->exit_status == 1)
			data->exit_status = 0;
		node = node->sibling;
		continue ;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command_tab.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 12:43:46 by dan               #+#    #+#             */
/*   Updated: 2024/02/11 14:25:15 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "parsing_utils.h"

int	is_env_var(char *str);
char	*get_env_var(t_Data *data, char *str, char buff[]);
void	insert_env_var(char **command, char *env_var, char buff[]);
void	check_if_env_var_and_get_it(t_Data *data, t_ast_nde **node, char **env_var, char buff[]);
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
/* typedef enum e_tok
{
	RAW,
	INVRT,
	SQUTE,
	IN_SQUTE,
	DQUTE,
	IN_DQUTE,
	EXP,
	PIPE,
	AND,
	OR,
	SCHEV_LFT,
	DCHEV_LFT,
	SCHEV_RGTH,
	DCHEV_RGTH,
	IO_FILE,
	SPCE,
	CMD,
	ARG_CMD,
	OPT_CMD,
	ARG_OPT	
}	t_tok; */

int	is_separator(t_ast_nde *node)
{
	if (node == NULL || node->token == PIPE
		|| node->token == AND || node->token == OR)
		return (1);
	else
		return (0);	
}

int	is_chevron(t_ast_nde *node)
{
	if (node->token == SCHEV_LFT || node->token == DCHEV_LFT ||
			node->token == SCHEV_RGTH || node->token == DCHEV_RGTH)
		return (1);
	else
		return (0);	
}

int	get_cmd_nbr(t_ast_nde *node)
{
	int cmd_nbr;
	
	cmd_nbr = 0;
	while (node)
	{
		if (is_chevron(node))
		{
			cmd_nbr++;
			if (is_separator(node->sibling))
			{
				ft_printf("HANDLE THIS ERROR!!!\n");
				return (0);
			}
			if (node->sibling->sibling)
			{
				node = node->sibling->sibling;
				if (!is_separator(node))
					cmd_nbr++;	
			}
			continue;
		}
		if ((node->token == PIPE || node->token == AND || node->token == OR) && (!is_chevron(node->sibling)))
			cmd_nbr++;
		node = node->sibling;
	}
	return (cmd_nbr);
}

void	fill_cmd_tab_tabs()
{

}

char	***create_command_tab(t_Data *data, t_ast_nde *node, char *envp[])
{
	char	***cmd_tab;
	int		cmd_nbr;
	
	cmd_nbr = get_cmd_nbr(node);
	ft_printf("cmd_nbr: %i\n", cmd_nbr);

	//create cmd_tab
	cmd_tab = (char ***)malloc(sizeof (char **) * cmd_nbr + 1);
	if (cmd_tab == NULL)
		return (NULL);
	cmd_tab[cmd_nbr] = NULL;
	
	fill_cmd_tab_tabs();
}





// void	get_command_nbr(t_ast_nde **current, int *tree_length)
// {
// 	(*tree_length) = 0;
// 	while (*current)
// 	{
// 		if ((*current)->token == AND || (*current)->token == OR)
// 			break ;
// 		if ((*current)->token != PIPE && (*current)->end
// 			- (*current)->start + 1)
// 			(*tree_length)++;
// 		*current = (*current)->sibling;
// 	}
// }



// char	**fill_command_tab(t_Data *data, char ***cmd_tab,
// 	t_ast_nde **node)
// {
// 	int			i;
// 	char		*env_var;
// 	char		buff[2000];

// 	if (data->exit_status && (*node)->sibling->sibling)
// 		(*node) = (*node)->sibling->sibling;
// 	i = 0;
// 	while (*node)
// 	{
// 		if ((*node)->token == AND || (*node)->token == OR)
// 			break ;
// 		env_var = NULL;
// 		check_if_env_var_and_get_it(data, node, &env_var, buff);
// 		if ((*node)->token != PIPE && (*node)->end - (*node)->start + 1)
// 		{
// 			(*cmd_tab)[i] = ft_strndup((*node)->start,
// 					(*node)->end - (*node)->start + 1);
// 			if ((*cmd_tab)[i] == NULL)
// 				return (NULL);
// 			if ((*node)->child->token == RAW || (*node)->child->token == DQUTE)
// 				if (env_var)
// 					insert_env_var(&((*cmd_tab)[i]), env_var, buff);
// 			i++;
// 		}
// 		(*node) = (*node)->sibling;
// 	}
// 	(*cmd_tab)[i] = NULL;
// 	return (*cmd_tab);
// }

// char	**create_command_tab(t_Data *data, t_ast_nde *node, char *envp[])
// {
// 	char		**cmd_tab;
// 	int			tree_length;
// 	t_ast_nde	*current;

// 	data->exit_status = 0;
// 	while (node)
// 	{
// 		current = node;
// 		get_command_nbr(&current, &tree_length);
// 		cmd_tab = (char **)malloc(sizeof(char *) * tree_length + 1);
// 		if (cmd_tab == 0)
// 			return (NULL);
// 		cmd_tab = fill_command_tab(data, &cmd_tab, &node);
// 		display_command_tab(cmd_tab);
// 		data->exit_status = pipex(cmd_tab, envp);
// 		if (node == NULL)
// 			break ;
// 		if (node->token == OR && data->exit_status == 0)
// 			data->exit_status = 1;
// 		if (node->token == OR && data->exit_status == 1)
// 			data->exit_status = 0;
// 		node = node->sibling;
// 		continue ;
// 	}
// }

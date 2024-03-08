/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_command_tab.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 17:38:25 by seblin            #+#    #+#             */
/*   Updated: 2024/03/08 16:40:39 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fill_command_tab.h"
void	print_node(t_ast_nde *node);
void	store_and_free_cmd_tab(char ***cmd_tab);
int	is_raw(t_ast_nde *node);
void	print_ast_sib(t_ast_nde *sib);

int	is_raw(t_ast_nde *node)
{
	if (node->token == RAW)
		return (1);
	return (0);
}


void	add_pipe_tab_to_tab(char ****cmd_tab, int *i)
{
	int j;
	
	j = 0;
	while ((*cmd_tab)[*i][j] && (*cmd_tab)[*i][j][0])
		j++;
	(*cmd_tab)[*i][j] = NULL;
	if ((*cmd_tab)[*i][0][0])
		(*i)++;
	(*cmd_tab)[*i][0][0] = '|';
	(*cmd_tab)[*i][0][1] = '\0';
	(*cmd_tab)[*i][1] = NULL;
	(*i)++;
}

void	create_chev_tab(char ****cmd_tab, t_ast_nde **current, int *i)
{
	char *chev;
	if ((*cmd_tab)[*i][0][0])
		(*i)++;
		
	if ((*current)->token == SCHEV_LFT)
		chev = "<";
	if ((*current)->token == SCHEV_RGTH)
		chev = ">";
	if ((*current)->token == DCHEV_LFT)
		chev = "<<";
	if ((*current)->token == DCHEV_RGTH)
		chev = ">>";
	(*current)->sibling->token = CHEV_FILE;
	ft_memcpy(&(*cmd_tab)[*i][0][0], chev, ft_strlen(chev));
	ft_memcpy(&(*cmd_tab)[*i][1][0], (*current)->sibling->child->start, (*current)->sibling->child->end - (*current)->sibling->child->start + 1);
	(*cmd_tab)[*i][2] = NULL;	
	(*i)++;
}

void	add_raw_to_cmd_tab(t_Data *data, char ****cmd_tab, t_ast_nde *current, int *i)
{
	int j;
	
	j = 0;
	while ((*cmd_tab)[*i][j] && (*cmd_tab)[*i][j][0])
		j++;
	(*cmd_tab)[*i][j] = get_node_str(data, current->child);
}

int	cmd_tab_error_check(t_ast_nde *node)
{
	//error management to be added here...
	return (1);
}

void	create_dollar_tab(t_Data *data, t_ast_nde **node, char ****cmd_tab, int *i)
{
	int j;
	char *env_var;
	env_var = get_node_str(data, (*node)->child);
	int	len;

	len = ft_strlen(env_var);
	j = 0;
	while ((*cmd_tab)[*i][j] && (*cmd_tab)[*i][j][0])
		j++;
	ft_memcpy((*cmd_tab)[*i][j], env_var, len + 1);
	(*cmd_tab)[*i][j + 1] = NULL;
}

void complete_raw_tab(t_Data *data, char ****cmd_tab, t_ast_nde *node, int *i)
{
	t_ast_nde *current;
	int j;
	
	j = 0;
	while ((*cmd_tab)[*i - 1][j] && (*cmd_tab)[*i - 1][j][0])
		j++;
	current = node->child->sibling;
	ft_strcat((*cmd_tab)[*i - 1][j - 1], get_node_str(data, current));
}

char	***fill_cmd_tab_tabs(t_Data *data, t_ast_nde *node, char ***cmd_tab)
{
	t_ast_nde	*current;
	int			i;
	int 		j;
	
	current = node;
	while (current)
	{
		if (cmd_tab_error_check(node) == 0)
		{
			ft_printf("ERROR!!!\n");
		}
		current = current->sibling;
	}
	i = 0;
	current = node;
	while (current && node)
	{
		while (!is_separator(current))
		{
			if (is_chevron(current))
			{
				create_chev_tab(&cmd_tab, &current, &i);
				if (current && is_separator(current->sibling->sibling) && current->sibling->child->sibling)
				{
					complete_raw_tab(data, &cmd_tab, current->sibling, &i);
				}
			}
			
			current = current->sibling;
		}
		while (node && !is_separator(node))
		{
			if (is_raw(node))
				add_raw_to_cmd_tab(data, &cmd_tab, node, &i);
			else if (node->child->token == DOLL)
				create_dollar_tab(data, &node, &cmd_tab, &i);
			node = node->sibling;
		}
		
		if (node && node->token == PIPE)
		{
			add_pipe_tab_to_tab(&cmd_tab, &i);
			node = node->sibling;
		}
		if (current && current->sibling)
			current = current->sibling;
		
	}
	j = 0;
	while ((cmd_tab)[i][j] && (cmd_tab)[i][j][0])
		j++;
	(cmd_tab)[i][j] = NULL;
	cmd_tab[i + 1] = NULL;
	return (cmd_tab);
}

/* 
while (!is_separator((*node)) && !is_chevron((*node)))
{
	if ((*node)->token == JOKER)
	{
		tab = ft_split((*node)->start, ' ');
		k = 0;
		while (tab[k])
		{
			(*cmd_tab)[*i][j++] = ft_strdup(tab[k]);
			free(tab[k]);
			k++;
		}
		(*cmd_tab)[*i][j] = NULL;
		if ((*node)->start)
		{
			free((*node)->start);
		}
		free(tab);
	}
	else if ((*node)->token == DOLL)
	{
		(*cmd_tab)[*i][j++] = get_node_str(data, (*node)->child);
		if ((*node)->start)
			free((*node)->start);
	}
	else
		(*cmd_tab)[*i][j++] = get_node_str(data, (*node)->child);
	(*node) = (*node)->sibling;
} */
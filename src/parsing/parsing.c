/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 15:18:58 by seblin            #+#    #+#             */
/*   Updated: 2024/02/24 18:05:14 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "parsing_utils.h"
#include "libft.h"
#include "stdio.h"
#include "ft_printf.h"
#include "minishell.h"

t_ast_nde	*copy_node(t_ast_nde *node);
t_ast_nde	*copy_node_child(t_ast_nde *node);
t_ast_nde	*set_qute_sib(char *str);
t_ast_nde	*sib_last(t_ast_nde *sib);
t_ast_nde	*set_pipe(t_ast_nde *node);
void		print_qute_sib(t_ast_nde *sib);
void		print_sib(t_ast_nde *sib);
t_ast_nde	*set_operator(t_ast_nde *node);
void	print_tree(t_ast_nde *node);
int	set_dollar(t_ast_nde *node);
void print_rslt(t_ast_nde *rslt, int flag);
char	*search_env_var(char *envp[], char *env_to_find);
void	free_sibling(t_ast_nde *sib);
void print_sibling(t_ast_nde *sib);
void	print_cmd(t_ast_nde *cmd);
void	free_tree(t_ast_nde *operator);
static void	leaf_tree(t_ast_nde *operator, t_ast_nde **rslt, t_ast_nde **rslt_sav, t_Data *data);

char* get_var(const t_ast_nde *node, t_Data *data)
{	
	char	*str;
	char	*var;	
	
	str = ft_strndup(node->start, node->end - node->start + 1);
	if (*(str + 1) == '?')
		var = ft_itoa(data->exit_status);
	else		
		var = search_env_var(data->envp_tab, ft_strjoin_up(str + 1, "=", 0, 0));	
	if (str)
		free(str);
//	ft_printf("var: -%s-", var);
	return (var);	
}
t_ast_nde *rebuild_dollar_str_node(char *str)
{
	t_ast_nde *str_node;

	str_node = NULL;
	if (str)
	{
		str_node = create_node(RAW);
		str_node->start = str;
		str_node->end = str + ft_strlen(str) - 1;
		str_node->child = copy_node(str_node);
		//free(str); //!!!!!!!!!!!!!!!!!
	}
	return (str_node);
}
char	*link_sibling(const t_ast_nde *node)
{
	char	*str;
	char	*node_str;
	
	str = NULL;
	if (node)
		node = node->child;
	while (node)
	{		
		node_str = ft_strndup(node->start, node->end - node->start + 1);
		if (str && node_str)
			str = ft_strjoin_up(str, node_str, 1, 1);
		else
			str = node_str;
		node = node->sibling;
	}
	return (str);
}

void	merge_str_and_sibling(char **str, const t_ast_nde *sibling)
{
	char	*new_str;
		
	new_str = NULL;	
	if (sibling && str)
	{		
		new_str = link_sibling(sibling);
		if (new_str)
		{
			if (*str)
				*str = ft_strjoin_up(*str, new_str, 1, 1);
			else if (!*str)
				*str = new_str;			
		}
	}
}

void	build_token_and_merge(const t_ast_nde *operator, char **str,  t_Data *data)
{
	char	*str_tok;
	
	str_tok = NULL;
	if (operator)
	{		
		if (operator->token == DOLL)
			str_tok = get_var(operator, data);
		else if (operator->token == JOKER)
			str_tok = wilcard_func(ft_strndup(operator->start, operator->end - operator->start + 1));
		if (str_tok)
		{
			if (str && *str)
				*str = ft_strjoin_up(*str, str_tok, 1, 0);//!!!
			else if (str)
				*str = str_tok;		
		}
	}
}
char	*rebuild_dollar_str(const t_ast_nde *operator, char *str, t_Data *data)
{		
	const t_ast_nde	*sibling_lft = NULL;
	const t_ast_nde	*sibling_rght = NULL;
	const t_ast_nde	*next_operator = NULL;

	if (operator && operator->child)
	{
		if (operator->child->child)
			sibling_lft = operator->child->child;
		if (operator->child->sibling && operator->child->sibling->child)
		{
			sibling_rght = operator->child->sibling->child;		
			if (operator->child->sibling->child->sibling)
				next_operator = operator->child->sibling->child->sibling;
		}
	}		
	merge_str_and_sibling(&str, sibling_lft);
	build_token_and_merge(operator, &str, data);			
	if (next_operator)			
		str = rebuild_dollar_str(next_operator, str, data);		
	else 		
		merge_str_and_sibling(&str, sibling_rght);
	return (str);
}



void	free_branch(t_ast_nde *raw)
{
	t_ast_nde *cont;
	
	cont = raw->child;
	free(raw);
	if (cont)
		free_sibling(cont->child);
	if (cont && cont->sibling)	
	{
		free_tree(cont->sibling);
		free(cont);
	}
}

void	free_tree(t_ast_nde *operator)
{	
	t_ast_nde *raw_lft;
	t_ast_nde *raw_rght;
	
	raw_lft = NULL;
	raw_rght = NULL;	
	if (operator)
	{
		raw_lft = operator->child;
		if (raw_lft)
			raw_rght = raw_lft->sibling;
		free(operator);
	}	
	if (raw_lft)	
		free_branch(raw_lft);	
	if (raw_rght)
		free_branch(raw_rght);	
}

void	print_raw_rght(t_ast_nde *raw_rght);
void	print_space_tree(t_ast_nde *node);
	
static t_ast_nde	*create_ast(char *str, t_Data *data)
{
	t_ast_nde	*root;
	t_ast_nde	*cmd_sav;
	t_ast_nde	*cmd;
	
	cmd_sav = NULL;
	root = create_node(RAW);
	root->start = str;
	root->end = str + ft_strlen(str) - 1;
	root->child = copy_node(root);
	root->child->child = copy_node(root);
	root->child->child->child = set_qute_sib(str);
	//print_qute_sib(root->child->child->child);	
	set_operator(root->child);
	leaf_tree(root, &cmd, &cmd_sav, data);	
	
	//print_tree(root->child->child->sibling);
	//print_cmd(cmd_sav);
	
	free_tree(root);
	return (cmd_sav);
}

t_ast_nde	*parse(char *str, t_Data *data)
{
	if (!*str)
		return (NULL);
	return (create_ast(str, data));	
}

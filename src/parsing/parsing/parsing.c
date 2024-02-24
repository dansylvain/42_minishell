/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 15:18:58 by seblin            #+#    #+#             */
/*   Updated: 2024/02/24 21:10:46 by seblin           ###   ########.fr       */
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 15:18:58 by seblin            #+#    #+#             */
/*   Updated: 2024/02/19 18:41:16 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "parsing_utils.h"
#include "libft.h"
#include "stdio.h"
#include "parsing_spce.h"
#include "parsing_qute.h"
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
//t_ast_nde	*set_space(t_ast_nde *node);
int	set_dollar(t_ast_nde *node);
void print_rslt(t_ast_nde *rslt, int flag);
char	*search_env_var(char *envp[], char *env_to_find);
void	free_sibling(t_ast_nde *sib);
// static void	leaf_tree(t_ast_nde *root, t_ast_nde **cmd, t_ast_nde **cmd_sav)
// {
// 	t_ast_nde	*head;
	
// 	head = root;
// 	while (head)
// 	{			
// 		if (head->token == PIPE)
// 		{				
// 			leaf_tree(head->child, cmd, cmd_sav);
// 			if (!head->child->child->child)			
// 				add_sibling(head->child, cmd, cmd_sav);			
// 			add_sibling(head->child->sibling, cmd, cmd_sav);
// 			return ;
// 		}		
// 		head = head->child;
// 	}	
// }

char* get_var(t_ast_nde *node, t_Data *data)
{	
	char	*str;
	char	*var;	
	
	str = ft_strndup(node->start, node->end - node->start + 1);
	if (*(str + 1) == '?')
		var = ft_itoa(data->exit_status);
	else
		var = search_env_var(data->envp_tab, ft_strjoin_up(str, "=", 1, 0));	
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
char	*link_sibling(t_ast_nde *node)
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

char	*rebuild_dollar_str(t_ast_nde *node, char *str, t_Data *data)
{	
	char		*str_lft;
	char		*str_rght;
	char		*str_tok;
	char		*str_join;
			
	str_lft = NULL;
	if (node->child && node->child->child)	
		str_lft = link_sibling(node->child->child);	
	if (!str)
		str = str_lft;
	else if (str && str_lft)
		str = ft_strjoin_up(str, str_lft, 1, 1);
	if (node->token == DOLL)
		str_tok = get_var(node, data);
	else if (node->token == JOKER)
		str_tok = "JOKER";
	if (str && str_tok)
		str = ft_strjoin_up(str, str_tok, 1, 0);//!!!
	else if (!str)
		str = str_tok;		
	if (str && node && node->child && node->child->sibling && node->child->sibling->child && node->child->sibling->child->sibling)	//operateur			
		str = rebuild_dollar_str(node->child->sibling->child->sibling, str, data);		
	else if (node->child && node->child->sibling && node->child->sibling->child)
	{
		str_rght = link_sibling(node->child->sibling->child); 
		if (str && str_rght)
			str = ft_strjoin_up(str, str_rght, 1, 1);	
			//str = ft_strjoin(str, str_rght);
	}	
	return (str);
}
t_ast_nde *copy_sibling2(t_ast_nde *node)
{
	t_ast_nde *child;
	t_ast_nde *new_node;
	t_ast_nde *new_node2;
	t_ast_nde *new_sibling;
	t_ast_nde *new_sibling_sav;
	
	new_sibling_sav = NULL;	
	new_node = NULL;
	new_node2 = NULL;
	child = NULL;
	if (node)
	{		
		child = node->child;
		while (child)
		{
			new_node = copy_node(child);
			add_sibling(new_node, &new_sibling, &new_sibling_sav);	
			child = child->sibling;
		}	
		new_node2 = copy_node(node);	
		new_node2->child = new_sibling_sav;
	}
	return (new_node2);
}
t_ast_nde *copy_sibling(t_ast_nde *node)
{
	t_ast_nde *child;
	t_ast_nde *new_node;
	t_ast_nde *new_sibling;
	t_ast_nde *new_sibling_sav;
	
	new_node = NULL;
	child = node->child;
	new_sibling_sav = NULL;	
	while (child)
	{
		new_node = copy_node(child);
		add_sibling(new_node, &new_sibling, &new_sibling_sav);	
		child = child->sibling;
	}	
	new_node = copy_node(node);	
	new_node->child = new_sibling_sav;
	return (new_node);
}

static void	leaf_tree(t_ast_nde *operator, t_ast_nde **rslt, t_ast_nde **rslt_sav, t_Data *data)
{	
	t_ast_nde	*next_operator;
	t_ast_nde	*raw_lft;
	t_ast_nde	*raw_rght;
	t_ast_nde	*tmp_op;
	char		*expand;
	
	expand = NULL;
	raw_lft = NULL;
	raw_rght = NULL;
	if (operator)
		raw_lft = operator->child;
	if (raw_lft)
	 	raw_rght = raw_lft->sibling;
	if (operator && (operator->token == DOLL || operator->token == JOKER))			
		return (add_sibling(rebuild_dollar_str_node(rebuild_dollar_str(operator, NULL, data)), rslt, rslt_sav));	
	else if (raw_lft && raw_lft->child)
	{					
		if (raw_lft->child->sibling)
			leaf_tree(raw_lft->child->sibling, rslt, rslt_sav, data);
		else
		{
		//add_sibling(raw_lft->child, rslt, rslt_sav);	
			add_sibling(copy_sibling2(raw_lft->child), rslt, rslt_sav);
		}
	}	
	if (operator && operator->token != SPCE)
	{ 		

		    // operator->child = copy_node(operator);
            // add_sibling(operator, rslt, rslt_sav);
		tmp_op = copy_node(operator);
		tmp_op->child = copy_node(operator);	
		
		add_sibling(tmp_op, rslt, rslt_sav);				
	}
	next_operator = NULL;
	if (raw_rght && raw_rght->child)
		next_operator = raw_rght->child->sibling;
	if (next_operator)
		leaf_tree(next_operator, rslt, rslt_sav, data);
	else if (raw_rght && raw_rght->child)	
	{
		// add_sibling(raw_rght->child, rslt, rslt_sav);
		add_sibling(copy_sibling2(raw_rght->child), rslt, rslt_sav);			
	}	
}

t_ast_nde	*ft_lstlast_sib(t_ast_nde *lst)
{
	if (!lst)
		return (NULL);
	while (lst->sibling)
		lst = lst->sibling;
	return (lst);
}

void	ft_lstadd_back_sib(t_ast_nde **lst, t_ast_nde *new)
{
	if (!lst || !new)
		return ;
	if (!*lst)
		*lst = new;
	else
		ft_lstlast_sib(*lst)->sibling = new;
}

t_ast_nde	*expand_vars(t_ast_nde *qute_sib)
{
	t_ast_nde *current;
	t_ast_nde *next_sibling;
	t_ast_nde *var_node;
	t_ast_nde *raw_node;
	t_ast_nde *exp_sib;
	
	int i;
	
	exp_sib = (t_ast_nde *)malloc(sizeof(t_ast_nde));
	if (exp_sib == NULL)
		return (NULL);
	exp_sib->sibling = NULL;
	
	

	var_node = NULL;
	current = qute_sib;
	while (current)
	{
		if (current->token == RAW || current->token == IN_DQUTE)
		{
			i = 0;
			raw_node = create_node(RAW);
			raw_node->start = &current->start[i];
			
			while (i < qute_sib->end + 1 - qute_sib->start)
			{
				if (qute_sib->start[i] == '$' && qute_sib->start[i + 1] && qute_sib->start[i + 1] != ' ')
				{
					if (i == 0)
						free (raw_node);
					else
					{
						raw_node->end = &current->start[i];
						ft_lstadd_back_sib(&exp_sib, raw_node);
					}
					


					// create env var node
					var_node = create_node(EXP);
					var_node->start = &qute_sib->start[i];
				}
				if (var_node && (qute_sib->start[i + 1] == ' ' || i == qute_sib->end - qute_sib->start))
				{
					var_node->end = &qute_sib->start[i];
					ft_lstadd_back_sib(&exp_sib, var_node);
					break;
				}
				i++;
			}
			

			if (var_node)
			{
				// ft_printf("var_node->start: %s\n", var_node->start);
				// ft_printf("starting_char: %c\n", var_node->start[0]);
				// ft_printf("ending_char: %c\n", var_node->end[0]);
			}
			// print_sib(exp_sib);
			
			// {
			// 	int i = 0;
			// 	while (i < (var_node->end - var_node->start) + 1)
			// 		write (1, &var_node->start[i++], 1);
			// 	ft_printf("\nvar_len = %i\nchar start: %c\nchar end: %c\n", var_node->end - var_node->start + 1, var_node->start[0], var_node->end[0]);
			// }
		}
		current = current->sibling;		
	}
	
	return (qute_sib);
}

t_ast_nde	*format_io(t_ast_nde* cmd)
{
	t_ast_nde	*actual;
	t_ast_nde	*format_cmd;
	t_ast_nde	*format_cmd_sav;
	t_ast_nde	*inter_cmd_tmp;
	
	format_cmd_sav = NULL;
	actual = cmd;
	while (actual)
	{	
		inter_cmd_tmp = actual;
		while (actual && actual->token != PIPE && actual->token != AND  && actual->token != OR)
		{
			if (actual->token == SCHEV_LFT || actual->token == DCHEV_LFT)			
			{
				add_sibling(copy_node_child(actual), &format_cmd, &format_cmd_sav);
				if (actual && actual->sibling && actual->sibling->token != PIPE && actual->sibling->token != AND  && actual->sibling->token != OR
					&& actual->sibling->token != SCHEV_LFT && actual->sibling->token != DCHEV_LFT)
				{
					add_sibling(copy_node_child(actual->sibling), &format_cmd, &format_cmd_sav);
					actual = actual->sibling;
				}
			}
			actual = actual->sibling;
		}
		actual = inter_cmd_tmp;
		while (actual && actual->token != PIPE && actual->token != AND  && actual->token != OR)
		{
			if (actual->token == SCHEV_LFT || actual->token == DCHEV_LFT)			
			{			
				if (actual && actual->sibling && actual->sibling->token != PIPE && actual->sibling->token != AND  && actual->sibling->token != OR
					&& actual->sibling->token != SCHEV_LFT && actual->sibling->token != DCHEV_LFT)
					actual = actual->sibling;				
			}
			else
				add_sibling(copy_node_child(actual), &format_cmd, &format_cmd_sav);
			actual = actual->sibling;
		}		
		if (actual)
		{
			add_sibling(copy_node_child(actual), &format_cmd, &format_cmd_sav);
			actual = actual->sibling;
		}	
	}
	return (format_cmd_sav);
}

t_ast_nde	*format_io2(t_ast_nde* cmd)
{
	t_ast_nde	*actual;
	t_ast_nde	*format_cmd;
	t_ast_nde	*format_cmd_sav;
	t_ast_nde	*inter_cmd_tmp;
	
	format_cmd_sav = NULL;
	actual = cmd;
	while (actual)
	{	
		inter_cmd_tmp = actual;
		while (actual && actual->token != PIPE && actual->token != AND  && actual->token != OR)
		{
			if (actual->token == SCHEV_RGTH || actual->token == DCHEV_RGTH)			
			{			
				if (actual && actual->sibling && actual->sibling->token != PIPE && actual->sibling->token != AND  && actual->sibling->token != OR
					&& actual->sibling->token != SCHEV_RGTH && actual->sibling->token != DCHEV_RGTH)
					actual = actual->sibling;
				// if (actual && actual->token != PIPE && actual->token != AND  && actual->token != OR)
				// 	actual = actual->sibling;
			}
			else
				add_sibling(copy_node_child(actual), &format_cmd, &format_cmd_sav);
			actual = actual->sibling;
		}		
		actual = inter_cmd_tmp;
		while (actual && actual->token != PIPE && actual->token != AND  && actual->token != OR)
		{
			if (actual->token == SCHEV_RGTH || actual->token == DCHEV_RGTH)			
			{
				add_sibling(copy_node_child(actual), &format_cmd, &format_cmd_sav);
				if (actual && actual->sibling && actual->sibling->token != PIPE && actual->sibling->token != AND  && actual->sibling->token != OR
					&& actual->sibling->token != SCHEV_RGTH && actual->sibling->token != DCHEV_RGTH)
				{
					add_sibling(copy_node_child(actual->sibling), &format_cmd, &format_cmd_sav);
					actual = actual->sibling;
				}
			}
			actual = actual->sibling;
		}		
		if (actual)
		{
			add_sibling(copy_node_child(actual), &format_cmd, &format_cmd_sav);
			actual = actual->sibling;
		}
	//	actual = actual->sibling;
	}
	return (format_cmd_sav);
}

void	free_tree(t_ast_nde *operator)
{
	t_ast_nde *cont;
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
	{
		cont = raw_lft->child;
		free(raw_lft);
		if (cont)
			free_sibling(cont->child);
		if (cont && cont->sibling)	
		{
			free_tree(cont->sibling);
			free(cont);
		}
	}
	cont = NULL;
	if (raw_rght)
	{
		cont = raw_rght->child;
		free(raw_rght);
		if (cont)
			free_sibling(cont->child);
		if (cont && cont->sibling)
		{
			free_tree(cont->sibling);
			free(cont);
		}
	}
}

void	print_raw_rght(t_ast_nde *raw_rght);
void	print_space_tree(t_ast_nde *node);
	
static t_ast_nde	*create_ast(char *str, t_Data *data)
{
	t_ast_nde	*root;
	t_ast_nde	*ast_res;
	t_ast_nde	*qute_sib;
	t_ast_nde	*spce_sib;
	t_ast_nde	*pip_sib;
	t_ast_nde	*parnths_sib;

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

	//print_tree(root->child->child->sibling);
	// if (root->child->child->sibling)
	// 	set_space(root->child->child->sibling->child);//exit(1);
	// else 
	// 	set_space(root->child);
	//exit(1);
	//ft_printf("space\n\n");
	
	// if (root->child && root->child->child && root->child->child->sibling && root->child->child->sibling->child && root->child->child->sibling->child->child)
	// 	print_space_tree(root->child->child->sibling->child->child->sibling);

	// else
	// 	print_space_tree(root->child);
//	ft_printf("end\n\n");//exit(1);
	//set_chevron();
	
	leaf_tree(root->child->child->sibling, &cmd, &cmd_sav, data);
	//leaf_tree(root, &cmd, &cmd_sav, data);
//	exit(1);
	// print_rslt(cmd_sav, 1);
	//ft_printf("\n\n");
	// cmd_sav = format_io(cmd_sav);
	
	//print_rslt(cmd_sav, 1);
	//ft_printf("\n\n");
	
	// t_ast_nde	*cmd_sav2 = cmd_sav;
	// while (cmd_sav2)
	// {	
	// 	if(cmd_sav2->token == RAW || cmd_sav2->token == DOLL)// || cmd_sav2->token == SCHEV_LFT || cmd_sav2->token == DCHEV_LFT || cmd_sav2->token == SCHEV_RGTH || cmd_sav2->token == DCHEV_RGTH)
	// 	{			
	// 		print_rslt(cmd_sav2->child, 0);
	// 		ft_printf(" ");
	// 	}
	// 	cmd_sav2 = cmd_sav2->sibling;
	// }
	// ft_printf("\n\n");
	
	//cmd_sav = format_io(cmd_sav);
	//print_rslt(cmd_sav, 1);
	//ft_printf("\n\n");
	// t_ast_nde	*cmd_sav3 = cmd_sav;
	// while (cmd_sav3)
	// {	
	// 	if(cmd_sav3->token == RAW || cmd_sav3->token == DOLL)// || cmd_sav2->token == SCHEV_LFT || cmd_sav2->token == DCHEV_LFT || cmd_sav2->token == SCHEV_RGTH || cmd_sav2->token == DCHEV_RGTH)
	// 	{			
	// 		print_rslt(cmd_sav3->child, 0);
	// 		ft_printf(" ");
	// 	}
	// 	cmd_sav3 = cmd_sav3->sibling;
	// }
	// ft_printf("\n\n");
	
	//cmd_sav = format_io2(cmd_sav);
	//if(cmd_sav->token == DOLL || cmd_sav2->token == SCHEV_LFT || cmd_sav2->token == DCHEV_LFT || cmd_sav2->token == SCHEV_RGTH || cmd_sav2->token == DCHEV_RGTH)
	//{
	// 	print_rslt(cmd_sav, 1);
	// 	ft_printf("\n\n");
	// //}
	// t_ast_nde	*cmd_sav4 = cmd_sav;
	// while (cmd_sav4)
	// {	
	// 	//if( cmd_sav4->token == DOLL || cmd_sav2->token == SCHEV_LFT || cmd_sav2->token == DCHEV_LFT || cmd_sav2->token == SCHEV_RGTH || cmd_sav2->token == DCHEV_RGTH)
	// 	//{			
	// 		print_rslt(cmd_sav4->child, 0);
	// 		ft_printf("z");
	// 	//}
	// 	cmd_sav4 = cmd_sav4->sibling;
	// }
	// ft_printf("\n\n");

	if (!cmd_sav)
	{
	//	ft_printf("commande sav fausle\n");
		ast_res = root->child->child;
	}
	else
		ast_res = cmd_sav;
	if (root && root->child && root->child->child && root->child->child->sibling)
	{
		free_tree(root->child->child->sibling);
	}
	// if (root && root->child && root->child->child && root->child->child->child)
	// {
	// 	free(root->child->child->child);
	// }
		
	// //	free(root->child->child);
	// if (root && root->child)
	// 	free(root->child);
	// if (root)
	// 	free(root);
	//free_tree(root);
	return (ast_res);
}

t_ast_nde	*parse(char *str, t_Data *data)
{
	if (!*str)
		return (NULL);
	return (create_ast(str, data));	
}
// int	tmp_main(void)
// {	
// 	char *str = " |cat <file1|\"rev\"|ca't'e |grep -n \" cmd1 | cmd2\"| >file2 cut -d':' -f1 ";
// 	ft_printf("\n%s\n", str);
// 	parse(str, data);
// 	return(0);
// }
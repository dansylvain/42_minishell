/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 15:18:58 by seblin            #+#    #+#             */
/*   Updated: 2024/03/14 16:26:57 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "test.h"

static int	is_double_token(t_ast_nde *node)
{
	t_tok	d_tok;

	d_tok = RAW;
	while (node)
	{
		if (node->token != RAW && !is_chevron(node) && node->token != JOKER && node->token != DOLL)
		{
			// if (d_tok < 0)
// 				return (display_error_free(ft_strjoin("minishell: syntax 
// error near unexpected token DTOK 0 ", translate_enum(d_tok))), 1);
			if (node->token == d_tok)
				return (display_error_free(ft_strjoin("minishell: syntax \
error near DOUBLEunexpected token ", translate_enum(d_tok))), 1);
		}
		d_tok = node->token;
		node = node->sibling;
	}
	return (0);
}

static void	set_root(t_ast_nde **root, char *str)
{
	*root = create_node(RAW);
	(*root)->start = str;
	(*root)->end = str + ft_strlen(str) - 1;
	(*root)->child = copy_node(*root);
	(*root)->child->child = copy_node(*root);
}

int	set_parenthesis(t_ast_nde *node);

t_Data	*get_data(char *envp[]);
int	exec_pipex(t_Data *data, char *cmd, char *envp[], int reset);
int	parse_par(char *str, t_Data *data, t_ast_nde *root);

int m_flag = 0;
int	f_flag = 0;
int	leaf_tree_par(t_ast_nde	*raw, t_Data *data)
{
	
	extern int p_flag;
	t_ast_nde	*token;
	t_ast_nde	*raw_lft;
	t_ast_nde	*middle;
	t_ast_nde	*raw_rght;
	int	or_flag;
	//p_flag = 0;
	or_flag = 0;
	token = NULL;
	raw_lft = NULL;;
	middle= NULL;
	raw_rght = NULL;
	//ft_printf("leaf!\n");
	
	
	f_flag++;
	if (raw && raw->child)
	{	
		///ft_printf("le raw fournit est ok\n");
		token = raw->child->sibling;	
		if (token)
		{
			//ft_printf("il y a un nouveau token\n");
			raw_lft = token->child;
			if (raw_lft)
			{
				middle = raw_lft->sibling;
				if (raw_lft->child)
				{
					// ft_printf("il y a un raw_left\n");					
					// print_node(raw_lft);
					// ft_printf("\n");
				//ft_printf("je vais executer pipex avec raw_left\n");
					char *tmp = ft_strndup(raw_lft->start, raw_lft->end - raw_lft->start + 1);
					store_or_free_cmd(tmp);
					// if (m_flag)
					// 	p_flag = 0;
					// else
					// 	p_flag = 1;
					m_flag = 0;
					p_flag = 2;
					or_flag = exec_pipex(data, tmp, data->envp_tab, 0);
					p_flag = 0;
					m_flag = 0;
					store_or_free_cmd(NULL);
					//free(tmp);
					// if (get_data(NULL)->exit_status)
					// {
					// 	ft_printf("il y a un ouille 1\n");
					// 	//ft_printf("ERROR PIEX\n");	
					// 	return (1);
					// }
					// ft_printf("je vais executer pipex avec raw_left %d\n", or_flag);			
				}
			}
			if (middle)
			{
				middle->start++;
				middle->end--;
				middle->child->start++;
				middle->child->end--;
		//	p_flag = 0;
				// ft_printf("il y a un middle\n");
				// print_node(middle);
				// ft_printf("\n");
				// ft_printf("je vais utiliser la recursive, donc si pas de nouveau token, il y aura pipex avec le raw middle, sans par\n");
			
				if (!or_flag)
				{
					// char *actual;

					// actual = middle->start;
					// while (*actual != '(' || actual != middle->end)
					// 	actual++;
					//or_flag = exec_pipex(data, ft_strndup(token->start + 1, token->end - token->start - 1), data->envp_tab, 0);
					char *tmp = ft_strndup(middle->start, middle->end - middle->start + 1);
					store_or_free_cmd_par(tmp);
					//	ft_printf("tmp: -%s-\n", tmp);
					m_flag = 1;	
					if (parse_par(tmp, data, middle))
					{
						//ft_printf("il y a un ouille 2\n");
						//free(tmp);
						//store_or_free_cmd(NULL);
						store_or_free_cmd_par(NULL);
						m_flag = 0;
						return (1);
					}
					m_flag = 0;
					
					//f_flag = 0;
					store_or_free_cmd_par(NULL);
				//	store_or_free_cmd(NULL);
				//	free(tmp);
					
								
				}
				
				raw_rght = middle->sibling;
			}			
			if (raw_rght && raw_rght->child)
			{
				
				// ft_printf("il y a un raw_rght\n");
				// print_node(raw_rght);
				// ft_printf("\n");
				// ft_printf("je vais utiliser la recursive, donc si pas de nouveau token, il y aura pipex avec le raw right, mais entier\n");
				// ft_printf("si pas de raw, return 0\n");
				m_flag = 0;
				if (leaf_tree_par(raw_rght, data))
				{
					m_flag = 0;
					//f_flag = 0;
					return (1);								
				}
				m_flag = 0;
				
				
			}						
		}
		else
		{	
			// ft_printf("il n'y a pas de nouveau token\n");
			// ft_printf("je vais donc executer pipex avec le raw fournit\n");
			// print_node(raw);
			//  ft_printf("\n");
			// if (!or_flag)
			// if (f_flag)			
			// 	p_flag = 2;			
			// else if (f_flag)
				
			if (m_flag)
				p_flag = 0;
			else
				p_flag = 1;
			
			char *tmp = ft_strndup(raw->start, raw->end - raw->start + 1);			
			store_or_free_cmd(tmp);
			//p_flag = 1;
			//ft_printf("tmp2: -%s-\n", tmp);
			or_flag = exec_pipex(data, tmp, data->envp_tab, 0);
			m_flag = 0;
		//	p_flag = 0;
			store_or_free_cmd(NULL);
			//free(tmp);
			// if (get_data(NULL)->exit_status)
			// {
		
			// 	return (1);
			// }
			return (0);				
		}
	}

	return (0);
}

// int	leaf_tree_par2(t_ast_nde	*raw, t_Data *data)
// {		
// 	t_ast_nde	*token;
// 	int			state;
	
// 	ft_printf("INO\n");
// 	if (raw && raw->child)
// 	{			ft_printf("INO 2\n");
// 		token = raw->child->sibling;
// 		if (token && token->child)
// 		{		
// 			ft_printf("il y a un nouveau token\n");				
// 			if (leaf_tree_par(token->child->sibling, data))
// 			{			
// 				print_node(token);
// 				exec_pipex(data, ft_strndup(token->start + 1, token->end - token->start - 1),  data->envp_tab, 0);;
// 			//	if (state)
// 				ft_printf("LEAAAAAAAAAAFFFFFF\n");					
// 			}
// 			leaf_tree_par(token->child->sibling->sibling, data);			
// 		}
// 		else
// 		{	
// 			ft_printf("pas de nouveau token\n");
// 			exec_pipex(data, ft_strndup(raw->start, raw->end - raw->start + 1), data->envp_tab, 0);
// 			return (0);				
// 		}
// 	}	
// 	return (0);
// }

int	parse_par(char *str, t_Data *data, t_ast_nde *root)
{
	
	t_ast_nde	*cmd_sav;
	t_ast_nde	*cmd;
	t_ast_nde	*quote;
	int			first_rec;
	// if (root)
	// {
	// 	ft_printf("parse par\n");
	// 	print_node(root);
	// 	ft_printf("\n");
	// }
	first_rec = 0;
	if (!*str)
		return (1);
	cmd_sav = NULL;
	exec_pipex(NULL, NULL, NULL, 1);
	if (!root)
	{
		first_rec = 1;
		set_root(&root, str);
		quote = set_qute_sib(str);		
		root->child->child->child = quote;
		if (!quote)
			return (free_tree(root), 1);
		store_or_free_tree_par(root);
		root = root->child;
	}
	//print_qute_sib(quote);
	if (set_parenthesis(root) < 0)
	{	
		if (first_rec)		
			store_or_free_tree_par(NULL);		
		// else if (str)
		// 	free(str);
		return (1);
	}
		
	if (leaf_tree_par(root, data))
	{	
		
		if (first_rec)		
			store_or_free_tree_par(NULL);		
		// else if (str)
		// 	free(str);
		return (1);
	}
	//store_or_free_cmd_par(NULL);
	//return (store_or_free_tree_par(NULL), 0);
	if (first_rec)
	{
		store_or_free_tree_par(NULL);	
		f_flag = 0;	
	}
	// else if (str)
	// 	free(str);
	return (0);
	//print_tree(root);
}

t_ast_nde	*parse(char *str, t_Data *data)
{
	t_ast_nde	*root;
	t_ast_nde	*cmd_sav;
	t_ast_nde	*cmd;
	t_ast_nde	*quote;
	
	if (!*str)
		return (NULL);
	cmd_sav = NULL;
	
	set_root(&root, str);
	quote = set_qute_sib(str);
	root->child->child->child = quote;		
	if (!quote)
		return (free_tree(root), NULL);	
	if (set_operator(root->child))
		return (free_tree(root), NULL);	
	leaf_tree(root, &cmd, &cmd_sav, data);
	if (is_double_token(cmd_sav))
		return (free_sibling_and_child(cmd_sav), free_tree(root), NULL);
	return (free_tree(root), cmd_sav);
}

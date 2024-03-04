/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 15:18:58 by seblin            #+#    #+#             */
/*   Updated: 2024/03/04 11:50:02 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	set_parenthesis(t_ast_nde *node);

// t_ast_nde	*parse(char *str, t_Data *data)
// {
// 	t_ast_nde	*root;
// 	t_ast_nde	*cmd_sav;
// 	t_ast_nde	*cmd;
// 	t_ast_nde	*quote;
	
// 	if (!*str)
// 		return (NULL);
// 	cmd_sav = NULL;
// 	root = create_node(RAW);
// 	root->start = str;
// 	root->end = str + ft_strlen(str) - 1;
// 	root->child = copy_node(root);
// 	root->child->child = copy_node(root);
// 	quote = set_qute_sib(str);
// 	if (!quote)
// 		return (free_tree(root), NULL);	
// 	root->child->child->child = quote;
// 	if (set_parenthesis(root->child))
// 		return (free_tree(root), NULL);
// 	leaf_tree(root, &cmd, &cmd_sav, data);
// 	// if (set_operator(root->child))
// 	// 	return (free_tree(root), NULL);	
// 	// leaf_tree(root, &cmd, &cmd_sav, data);
// 	//print_cmd(cmd_sav);	
// 	return (free_tree(root), cmd_sav);
// }



// #include "parsing.h"
// int	set_parenthesis(t_ast_nde *node);
void	print_node(t_ast_nde *node);
void	exec_pipex(t_Data *data, char *cmd, char *envp[]);

int	leaf_tree_par(t_ast_nde	*raw, t_Data *data, char *envp[])
{
	t_ast_nde	*token;
	t_ast_nde	*raw_lft;
	t_ast_nde	*middle;
	t_ast_nde	*raw_rght;
	
	token = NULL;
	raw_lft = NULL;;
	middle= NULL;
	raw_rght = NULL;
	ft_printf("leaf!\n");
	if (raw && raw->child)
	{	
		ft_printf("le raw fournit est ok\n");
		token = raw->child->sibling;	
		if (token)
		{		
			ft_printf("il y a un nouveau token\n");
			raw_lft = token->child;
			if (raw_lft)
			{
				middle = raw_lft->sibling;
				if (raw_lft->child)
				{
					ft_printf("il y a un raw_left\n");
					raw_lft->start++;
					print_node(raw_lft);
					ft_printf("\n");
					ft_printf("je vais executer pipex avec raw_left\n");
					exec_pipex(data, ft_strndup(raw_lft->start, raw_lft->end - raw_lft->start + 1), envp);
				
				}
			}
			if (middle)
			{
				ft_printf("il y a un middle\n");
				middle->start++;
				middle->end--; 
				print_node(middle);
				ft_printf("\n");
				ft_printf("je vais utiliser la recursive, donc si pas de nouveau token, il y aura pipex avec le raw middle, sans par\n");
				leaf_tree_par(middle, data, envp);
				//exec_pipex(data, ft_strndup(token->start + 1, token->end - token->start - 1), envp);
				raw_rght = middle->sibling;
			}			
			if (raw_rght && raw_rght->child)
			{
				ft_printf("il y a un raw_rght\n");
				raw_rght->end--;
				print_node(raw_rght);
				ft_printf("\n");
				ft_printf("je vais utiliser la recursive, donc si pas de nouveau token, il y aura pipex avec le raw right, mais entier\n");
				ft_printf("si pas de raw, return 0\n");
				leaf_tree_par(raw_rght, data, envp);
				//exec_pipex(data, ft_strndup(raw_lft->start, raw_lft->end - raw_lft->start + 1), envp);				
			}		
			//leaf_tree_par(token->child->sibling->sibling, data, envp);			
		}
		else
		{	
			ft_printf("il n'y a pas de nouveau token\n");
			ft_printf("je vais donc executer pipex avec le raw fournit\n");
			print_node(raw);
			ft_printf("\n");
			exec_pipex(data, ft_strndup(raw->start, raw->end - raw->start + 1), envp);
			return (0);				
		}
	}
	else
		ft_printf("le raw fournit est null\n");
	return (0);
}

int	leaf_tree_par2(t_ast_nde	*raw, t_Data *data, char *envp[])
{		
	t_ast_nde	*token;
	int			state;
	
	ft_printf("INO\n");
	if (raw && raw->child)
	{			ft_printf("INO 2\n");
		token = raw->child->sibling;
		if (token && token->child)
		{		
			ft_printf("il y a un nouveau token\n");				
			if (leaf_tree_par(token->child->sibling, data, envp))
			{			
				print_node(token);
				 exec_pipex(data, ft_strndup(token->start + 1, token->end - token->start - 1), envp);
			//	if (state)
				ft_printf("LEAAAAAAAAAAFFFFFF\n");					
			}
			leaf_tree_par(token->child->sibling->sibling, data, envp);			
		}
		else
		{	
			ft_printf("pas de nouveau token\n");
			exec_pipex(data, ft_strndup(raw->start, raw->end - raw->start + 1), envp);
			return (0);				
		}
	}	
	return (0);
}

t_ast_nde	*parse_par(char *str, t_Data *data, char *envp[])
{
	t_ast_nde	*root;
	t_ast_nde	*cmd_sav;
	t_ast_nde	*cmd;
	t_ast_nde	*quote;
	
	if (!*str)
		return (NULL);
	cmd_sav = NULL;
	root = create_node(RAW);
	root->start = str;
	root->end = str + ft_strlen(str) - 1;
	root->child = copy_node(root);
	root->child->child = copy_node(root);
	quote = set_qute_sib(str);
	if (!quote)
		return (free_tree(root), NULL);
	print_qute_sib(quote);
	root->child->child->child = quote;
	if (set_parenthesis(root->child))
		;//return (free_tree(root), NULL);
	leaf_tree_par(root->child, data, envp);
	//print_tree(root);
	//exit(1);	
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
	root = create_node(RAW);
	root->start = str;
	root->end = str + ft_strlen(str) - 1;
	root->child = copy_node(root);
	root->child->child = copy_node(root);
	quote = set_qute_sib(str);
	if (!quote)
		return (free_tree(root), NULL);	
	root->child->child->child = quote;		
	if (set_operator(root->child))
		return (free_tree(root), NULL);	
	leaf_tree(root, &cmd, &cmd_sav, data);
	// print_cmd(cmd_sav);	
	return (free_tree(root), cmd_sav);
}

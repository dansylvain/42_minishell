// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   parsing_wip.c                                      :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/01/28 16:18:05 by seblin            #+#    #+#             */
// /*   Updated: 2024/01/31 14:05:37 by seblin           ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include <unistd.h>
// #include "parsing_utils.h"
// #include "libft.h"

// #include "stdio.h"

// static int	is_other(char *str)
// {
// 	return (!(*(str - 1) != '\\' && (*str == '\'' || *str == '\"')));
// }

// static int	is_qute(char *str, char qute)
// {
// 	return (*(str - 1) != '\\' && *str == qute);
// }

// static void	set_other_nde(t_ast_nde *other, char **str)
// {
// 	other->start = *str;
// 	other->end = *str;
	
// 	while (*++(*str))
// 	{
// 		if (!is_other(*str))			
// 			break ;
// 		other->end = *str;			
// 	}	
// }

// static int set_qute_nde2(t_ast_nde *qute_nde, char qute,
// 	t_ast_nde *sibling_sav, char **str)
// {
// 	qute_nde->start = *str;
// 	while (*++(*str))
// 	{
// 		if (is_qute(*str, qute))
// 		{		
// 			qute_nde->end = (*str)++;		
// 			break ;
// 		}		
// 	}
// 	if (!qute_nde->end)
// 	{
// 		ft_putstr_fd("quote error\n", 2);
// 		free_sib(sibling_sav);
// 		free_sib(qute_nde);
// 		return (1);
// 	}
// 	return (0);
// }
// static void	link_qute_node(t_tok tok, char qute, t_ast_nde **qute_sibling,
// 	t_ast_nde **qute_sibling_sav, char **str)
// {
// 	t_ast_nde	*new_nde;

// 	new_nde = create_node(tok);
// 	set_qute_nde2(new_nde, qute, *qute_sibling_sav, str); 	
// 	add_sibling(new_nde, qute_sibling, qute_sibling_sav);
// }

// static t_ast_nde	*set_qute_sib(char *str)
// {
// 	t_ast_nde	*qute_sibling_sav;
// 	t_ast_nde	*qute_sibling;
// 	t_ast_nde	*other_nde;

// 	qute_sibling_sav = NULL;
// 	while (*str)
// 	{
// 		if (is_qute(str, '\''))		
// 			link_qute_node(SQUTE, '\'', &qute_sibling, &qute_sibling_sav, &str);		
// 		else if (is_qute(str, '\"'))		
// 			link_qute_node(DQUTE,'\"', &qute_sibling, &qute_sibling_sav, &str);		
// 		else
// 		{
// 			other_nde = create_node(NONE); 
// 			set_other_nde(other_nde, &str);
// 			add_sibling(other_nde, &qute_sibling, &qute_sibling_sav);
// 		}	
// 	}
// 	return (qute_sibling_sav);
// }

// void	print_qute_sib(t_ast_nde *sib)
// {
// 	int	i;	
// 	int	color;
// 	int	back_color;
	
// 	while (sib)
// 	{
// 		if (sib->token == NONE)
// 		{
// 			color = 32;
// 			back_color = 41;	
// 		}
// 		else if (sib->token == SQUTE)
// 		{
// 			color = 31;
// 			back_color = 40;	
// 		}
// 		else if (sib->token == DQUTE)
// 		{
// 			color = 34;
// 			back_color = 45;	
// 		}
// 		i = 0;
// 		while (sib->start + i <= sib->end)
// 			printf("\033[%d;%dm%c\033[0m", color, back_color, sib->start[i++]);		
// 		sib = sib->sibling;		
// 	}
// 	printf("\n");
// }

// static void	*free_spce_nde_if_empty2(t_ast_nde *spce_nde, int *flag)
// {
// 	if (!spce_nde->start)
// 	{
// 		*flag = 0;
// 		free(spce_nde);
// 	}
// 	return (NULL);
// }

// t_ast_nde	*set_space_nde2(t_ast_nde *node)
// {
// 	static t_ast_nde	*spce_nde;
// 	static int			flag;

// 	if (!flag)
// 		spce_nde = create_node(SPACE);
// 	while (node->start <= node->end && ft_isspace(*node->start))
// 		node->start++;
// 	while (node->start <= node->end && !ft_isspace(*node->start))
// 	{
// 		if (!spce_nde->start)
// 			spce_nde->start = node->start;
// 		spce_nde->end = node->start++;
// 	}
// 	if (spce_nde->start && (node->start <= node->end || !*node->start))
// 	{
// 		flag = 0;
// 		return (spce_nde);
// 	}
// 	flag = 1;
// 	return (free_spce_nde_if_empty2(spce_nde, &flag));
// }

// t_ast_nde	*filter_wrapper_spce2(t_ast_nde *node,
// 									t_ast_nde *(*filter)(t_ast_nde *node))
// {
// 	t_ast_nde	*res_nde;
// 	t_ast_nde	*res_sibling;
// 	t_ast_nde	*res_sibling_sav;

// 	res_sibling_sav = NULL;	
// 	while (node)
// 	{
// 		if (node->token == NONE)
// 		{			
// 			res_nde = filter(node);
// 			if (res_nde)
// 			{
// 				add_sibling(res_nde, &res_sibling, &res_sibling_sav);				
// 				//continue ;
// 				printf("yep\n");	
// 			}
// 			else
// 			{				
// 				printf("youpi\n");	
// 				node = node->sibling;					
// 			}
// 		}
// 		else
// 		{
// 			//add_sibling(node, &res_sibling, &res_sibling_sav);
// 			node = node->sibling;		
// 			printf("salut\n");	
// 		}
// 	}
// 	return (res_sibling_sav);
// }

// void	print_spce_sib(t_ast_nde *sib)
// {
// 	int	i;	
// 	int	color;
	
// 	color = 31;
// 	while (sib)
// 	{		
// 		i = 0;
// 		while (sib->start + i <= sib->end)
// 			printf("\033[%dm%c\033[0m", color, sib->start[i++]);
// 		color = (color - 31 + 1) % 7 + 31;	
// 		sib = sib->sibling;
// 	}
// 	printf("\n");
// }
// #include "parsing_spce.h"
// #include "parsing_qute.h"
// static char	**create_ast(char *str)
// {
// 	char		**ast_res;
// 	t_ast_nde	*qute_sib;
// 	t_ast_nde	*spce_sib;
// 	t_ast_nde	*parnths_sib;
	
// 	qute_sib = set_qute_sib(str);
// 	print_qute_sib(qute_sib);
// 	spce_sib = filter_wrapper_spce2(qute_sib, set_space_nde2);
// 	print_spce_sib(spce_sib);
// 	free_sib(qute_sib);
// 	return (ast_res);
// }

// char	*parse(char *str)
// {
// 	if (!*str)
// 		return (NULL);
// 	create_ast(str);
// 	return ("ok");
// }
// int	tmp_main(void)
// {
// 	//char *str = "x'e \"s 't \"\"ju\"' m\"oi' bie '   n ";
// 	char *str = "x 'e \"s '  t \"\"ju\"' m\"oi' bie '   n ";
// 	printf("%s\n", str);
// 	parse(str);
// 	return(0);
// }
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 10:29:44 by svidot            #+#    #+#             */
/*   Updated: 2024/03/17 14:11:07 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "operator.h"
#include "test.h"

static t_ast_nde	*create_token(t_tok simpl_tok, t_tok doubl_tok,
	char *actual, char char_tok)
{
	t_ast_nde	*token_nde;

	token_nde = create_node(simpl_tok);
	token_nde->start = actual;
	token_nde->end = actual;
	if (*(actual + 1) == char_tok)
	{
		token_nde->token = doubl_tok;
		token_nde->end = ++actual;
	}
	return (token_nde);
}

static t_ast_nde	*search_token(char *actual)
{
	t_ast_nde	*token_nde;

	if (*actual == '|')
		return (create_token(PIPE, OR, actual, '|'));
	else if (*actual == '&' && *(actual + 1) == '&')
	{
		token_nde = create_node(AND);
		token_nde->start = actual;
		token_nde->end = ++actual;
		return (token_nde);
	}
	else if (*actual == '<')
		return (create_token(SCHEV_LFT, DCHEV_LFT, actual, '<'));
	else if (*actual == '>')
		return (create_token(SCHEV_RGTH, DCHEV_RGTH, actual, '>'));
	return (NULL);
}

static t_ast_nde	*create_token_node(t_ast_nde *sib)
{
	t_ast_nde	*token_nde;
	char		*actual;

	while (sib)
	{
		actual = sib->start;
		while (sib->token == RAW && actual <= sib->end)
		{
			token_nde = search_token(actual);
			if (token_nde)
				return (token_nde);
			actual++;
		}
		sib = sib->sibling;
	}
	return (NULL);
}

static int		is_only_space(char *start, char *end)
{	
	while (start <= end)
	{
		if (!ft_isspace(*start))
			return (0);
		start++;
	}
	return (1);
}

int	is_sibling_only_space(t_ast_nde *sib)
{	
	while (sib)
	{			
		if (sib->start && !is_only_space(sib->start, sib->end))		
			return (0);		
		sib = sib->sibling;
	}	
	return (1);
}

int	is_prev_par(t_ast_nde *sib_quote, char *token)
{
	char	*actual;
	char	*ex_char;
	ft_printf("is_prev, token -%c-\n", *token);
	ex_char = NULL;
	while (sib_quote)
	{
		ft_printf("is_prev new sib\n");
		if (sib_quote->token == RAW)
		{
			actual = sib_quote->start;
			while (actual && actual <= sib_quote->end)
			{
				ft_printf("actual: -%c-", *actual);
				if (!ft_isspace(*actual))
					ex_char = actual;
				ft_printf("ex_char: -%c-", *ex_char);
				if (actual == token)// && ex_char && *ex_char == '(')
				{
					ft_printf("we have a match act-%c tok-%c\n", *actual, *token);
					return (1);
				}
				actual++;
			}
			ft_printf("actual: end-\n");
		}
		sib_quote = sib_quote->sibling;
	}
	return (0);
}

// int	is_near_par(char *cmd_start, t_ast_nde *sib_quote, t_ast_nde *token)
// {	
// 	int			sense;
// 	int			i;	
// 	char		*actual;

// 	if (cmd_start)
// 		actual = forward_token_to_sib_quote(sib_quote, token->start);
// 	else
// 		actual = forward_token_to_sib_quote(sib_quote, token->end);
// 	i = 0;
// 	sense = 1;
// 	if (cmd_start)
// 		sense = -sense;	
// 	while (*(actual + (i * sense)) || actual + (i * sense) >= cmd_start)
// 	{
// 		if (*actual == '?')
// 		if (cmd_start && *actual == '(')
// 			return (1);
// 		else if (!cmd_start && *actual == ')')
// 			return (0);
// 		i++;
// 	}
// 	return (0);	
// }

static int	token_child_handle(t_ast_nde *sib_cont,
	t_ast_nde *raw_lft, t_ast_nde *raw_rght, t_ast_nde *token)
{
	t_ast_nde	*sib;
	extern int p_flag;
	
	sib = sib_cont->child;
	raw_lft = create_token_child(sib_cont, token);
	raw_rght = raw_lft->sibling;
	token->child = raw_lft;
	fill_child(sib, raw_lft->child, raw_rght->child, token);
	//p_flag = 3;	
	if (!p_flag) 
	{	
			//ft_putstr_fd("je suis pflag 0, 1-1\n", 2);
		if (raw_lft->child && raw_lft->child->child && !is_sibling_only_space(raw_lft->child->child))
			set_space(raw_lft);
		else if ((token->token == AND || token->token == OR || token->token == PIPE))// && 
			// !is_prev_par(store_or_free_tree_par(create_node(RAW))->child->child->child, token->start))
			return (display_error_free(ft_strjoin("minishell: raw letf syntax error near \
unexpected token ", translate_enum(token->token))), 1);

			//ft_printf(" else raw right flag: %d\n", p_flag);
		if (raw_rght->child && raw_rght->child->child && !is_sibling_only_space(raw_rght->child->child))
			return ((set_operator(raw_rght)));	
		else if ((token->token == AND || token->token == OR || token->token == PIPE
			|| is_chevron(token)))// && !is_near_par(NULL, store_or_free_tree_par((t_ast_nde *){0})->child->child->child, token))
			return (display_error_free(ft_strjoin("minishell: raw right syntax error near \
unexpected token ", translate_enum(token->token))), 1);

	}	
	if (p_flag == 1)
	{	ft_putstr_fd("je suis pflag 1, 0-1\n", 2);
		if (raw_lft->child)
 			set_space(raw_lft);
			
		if (raw_rght->child && raw_rght->child->child && !is_sibling_only_space(raw_rght->child->child))
			return ((set_operator(raw_rght)));	
		else if (token->token == AND || token->token == OR || token->token == PIPE
			|| is_chevron(token))
			return (display_error_free(ft_strjoin("minishell: MID 1 raw right syntax error near \
unexpected token ", translate_enum(token->token))), 1);	
	}	
	if (p_flag == 2)
	{	ft_putstr_fd("je suis pflag 2, 1-0\n", 2);
		if (raw_lft->child && raw_lft->child->child && !is_sibling_only_space(raw_lft->child->child))
			set_space(raw_lft);
		else if (token->token == AND || token->token == OR || token->token == PIPE)
			return (display_error_free(ft_strjoin("minishell: MID 2 raw left syntax error near \
unexpected token ", translate_enum(token->token))), 1);

		if (raw_rght->child)
			return ((set_operator(raw_rght)));
	}
	if (p_flag == 3)
	{//ft_putstr_fd("je suis pflag 3, 0-0\n", 2);
		if (raw_lft->child)
			set_space(raw_lft);

		if (raw_rght->child)
			return ((set_operator(raw_rght)));			
	}
	return (0);
}

int	set_operator(t_ast_nde *node)
{
	t_ast_nde	*sib;
	t_ast_nde	*sib_cont;
	t_ast_nde	*token;
	t_ast_nde	*raw_lft;
	t_ast_nde	*raw_rght;

	sib_cont = node->child;
	sib = sib_cont->child;
	token = create_token_node(sib);
	sib_cont->sibling = token;
	if (token)
		return (token_child_handle(sib_cont, raw_lft, raw_rght, token));
	set_space(node);
	return (0);
}

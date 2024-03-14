// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   cmd_error.c                                        :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/03/14 12:57:30 by seblin            #+#    #+#             */
// /*   Updated: 2024/03/14 13:06:10 by seblin           ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// //#include "test.h"
// #include "parsing_utils.h"

// t_ast_nde	*set_qute_sib(char *str);

// void	is_op()
// {
// 	return ()
// }

// void	cmd_error(char *cmd)
// {
// 	t_ast_nde	*quote_sib;
	
// 	quote_sib = set_qute_sib(cmd);
// 	while (quote_sib)
// 	{
// 		if (quote_sib->token == RAW)
		
// 		quote_sib = quote_sib->sibling;
// 	}
// }

// static int	is_double_token(t_ast_nde *node)
// {
// 	t_tok	d_tok;

// 	d_tok = RAW;
// 	while (node)
// 	{
// 		if (node->token != RAW && !is_chevron(node) && node->token != JOKER && node->token != DOLL)
// 		{
// 			// if (d_tok < 0)
// // 				return (display_error_free(ft_strjoin("minishell: syntax 
// // error near unexpected token DTOK 0 ", translate_enum(d_tok))), 1);
// 			if (node->token == d_tok)
// 				return (display_error_free(ft_strjoin("minishell: syntax \
// error near unexpected token ", translate_enum(d_tok))), 1);
// 		}
// 		d_tok = node->token;
// 		node = node->sibling;
// 	}
// 	return (0);
// }
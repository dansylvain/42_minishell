/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 10:03:27 by svidot            #+#    #+#             */
/*   Updated: 2024/03/07 13:25:33 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_UTILS_H
# define PARSING_UTILS_H

typedef enum e_tok
{
	RAW,	
	INVRT,
	PRTH,
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
	DOLL,
	JOKER,
	IO_FILE,
	SPCE,
	CMD,
	ARG_CMD,
	OPT_CMD,
	ARG_OPT,
	CHEV_FILE
}	t_tok;

typedef struct s_ast_nde
{
	t_tok				token;
	char				*start;
	char				*end;
	struct s_ast_nde	*child;
	struct s_ast_nde	*sibling;
}	t_ast_nde;

t_ast_nde	*create_node(t_tok token);
void		add_sibling(t_ast_nde *node, t_ast_nde **sibling,
				t_ast_nde **sibling_sav);
t_ast_nde	*copy_node(t_ast_nde *node);
t_ast_nde	*copy_node_child(t_ast_nde *node);
t_ast_nde	*copy_node_and_child(t_ast_nde *node);

t_ast_nde	*ft_lstlast_sib(t_ast_nde *lst);
void		ft_lstadd_back_sib(t_ast_nde **lst, t_ast_nde *new);
t_ast_nde	*sib_last(t_ast_nde *sib);

void		free_tree(t_ast_nde *operator);
void		free_sibling(t_ast_nde *sib);
void		free_sibling_and_child(t_ast_nde *sib);

#endif

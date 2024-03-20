/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 10:03:27 by svidot            #+#    #+#             */
/*   Updated: 2024/03/18 06:55:27 by seblin           ###   ########.fr       */
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
	STAT,
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

t_ast_nde	*store_or_free_tree_par(t_ast_nde *root);
void		store_or_free_cmd(char *cmd);
void		store_or_free_cmd_par(char *cmd);
void		free_tree_par(t_ast_nde *operator);
void		free_tree(t_ast_nde *operator);
void		free_sibling(t_ast_nde *sib);
void		free_sibling_and_child(t_ast_nde *sib);

#endif

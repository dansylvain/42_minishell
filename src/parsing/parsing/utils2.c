/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 20:57:31 by seblin            #+#    #+#             */
/*   Updated: 2024/02/24 21:02:12 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_utils.h"
#include <stdlib.h>

char	*translate_enum(t_tok token)
{
	if (token == AND)
		return "&&";
	else if (token == OR)
		return "||";
	else if (token == PIPE)
		return "|";
	else if (token == SCHEV_LFT)
		return "<";
	else if (token == DCHEV_LFT)
		return "<<";
	else if (token == SCHEV_RGTH)
		return ">";
	else if (token == DCHEV_RGTH)
		return ">>";	
	return (NULL);
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

t_ast_nde	*sib_last(t_ast_nde *sib)
{	
	while (sib && sib->sibling)		
		sib = sib->sibling; 
	return (sib);
}
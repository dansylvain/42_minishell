/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 20:57:31 by seblin            #+#    #+#             */
/*   Updated: 2024/02/29 13:41:48 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils2.h"

char	*translate_enum(t_tok token)
{
	if (token == AND)
		return ("'&&'\n");
	else if (token == OR)
		return ("'||'\n");
	else if (token == PIPE)
		return ("'|'\n");
	else if (token == SCHEV_LFT)
		return ("'<'\n");
	else if (token == DCHEV_LFT)
		return ("'<<'\n");
	else if (token == SCHEV_RGTH)
		return ("'>'\n");
	else if (token == DCHEV_RGTH)
		return ("'>>'\n");
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 20:57:31 by seblin            #+#    #+#             */
/*   Updated: 2024/03/17 18:08:57 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils2.h"

char	*translate_enum(t_tok token)
{
	if (token == AND)
		return ("`&&'\n");
	else if (token == OR)
		return ("`||'\n");
	else if (token == PIPE)
		return ("`|'\n");
	else if (token == SCHEV_LFT)
		return ("`<'\n");
	else if (token == DCHEV_LFT)
		return ("`<<'\n");
	else if (token == SCHEV_RGTH)
		return ("`>'\n");
	else if (token == DCHEV_RGTH)
		return ("`>>'\n");
	return (NULL);
}

int	is_only_space_op(char *start, char *end)
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
		if (sib->start && !is_only_space_op(sib->start, sib->end))
			return (0);
		sib = sib->sibling;
	}
	return (1);
}

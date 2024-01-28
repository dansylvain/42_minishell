/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_wip.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 16:18:05 by seblin            #+#    #+#             */
/*   Updated: 2024/01/28 16:29:27 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "parsing_utils.h"

char	**create_ast(char *str)
{
	char		**ast_res;
	t_ast_nde	*qute_sib;
	
	qute_sib = set_quote_nde(argv);

	free_sib(qute_sib);
	return (ast_res);
}

void	parse(char *str)
{
	if (!*str)
		return (NULL);
	
}
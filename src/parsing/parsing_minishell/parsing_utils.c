/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 14:37:11 by svidot            #+#    #+#             */
/*   Updated: 2024/02/03 15:34:07 by svidot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_utils.h"
#include <stdlib.h>

t_ast_nde	*copy_node(t_ast_nde *node)
{
	t_ast_nde	*new_node;
	
	new_node = create_node(node->token);
	if (!new_node)
		return (NULL);
	new_node->start = node->start;
	new_node->end = node->end;
	return (new_node);	
}

t_ast_nde	*sib_last(t_ast_nde *sib)
{	
	while (sib && sib->sibling)		
		sib = sib->sibling; 
	return (sib);
}
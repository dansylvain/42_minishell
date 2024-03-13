/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command_tab_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:53:57 by dan               #+#    #+#             */
/*   Updated: 2024/03/13 07:27:40 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "create_command_tab_utils.h"

/**========================================================================
 *                           is_separator
 *========================================================================**/
int	is_separator(t_ast_nde *node)
{
	if (node == NULL || node->token == PIPE
		|| node->token == AND || node->token == OR)
		return (1);
	else
		return (0);
}

/**========================================================================
 *                           is_chevron
 *========================================================================**/
int	is_chevron(t_ast_nde *node)
{
	if (node->token == SCHEV_LFT || node->token == DCHEV_LFT
		|| node->token == SCHEV_RGTH || node->token == DCHEV_RGTH)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

/**========================================================================
 *                           get_node_str
 *========================================================================**/
char	*get_node_str(t_ast_nde *node)
{
	char	str[20000];
	int		index;

	index = 0;
	ft_bzero(str, 20000);
	while (node)
	{
		if (node->token != SQUTE && node->token != DQUTE)
		{
			ft_memcpy(&(str[index]), node->start, node->end - node->start + 1);
			index += node->end - node->start + 1;
		}
		node = node->sibling;
	}
	return (ft_strdup(str));
}

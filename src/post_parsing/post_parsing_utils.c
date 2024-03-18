/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_parsing_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 16:54:17 by seblin            #+#    #+#             */
/*   Updated: 2024/03/18 16:58:01 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "post_parsing_utils.h"

/**========================================================================
 *                           is_pipeline
 *========================================================================**/
int	is_pipeline(t_ast_nde *cmd_tab_node_sav)
{
	while (cmd_tab_node_sav)
	{
		if (cmd_tab_node_sav->token == PIPE || is_chevron(cmd_tab_node_sav))
			return (1);
		cmd_tab_node_sav = cmd_tab_node_sav->sibling;
	}
	return (0);
}

char	*ft_delchar(char *s)
{
	char	*s_save;

	s_save = s;
	while (s && *s)
	{
		*s = *(s + 1);
		s++;
	}
	return (s_save);
}

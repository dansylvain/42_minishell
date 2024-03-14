/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_command_tab_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 07:50:04 by dan               #+#    #+#             */
/*   Updated: 2024/03/14 13:38:41 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fill_command_tab_utils.h"
#include "ft_printf.h"

/**========================================================================
 *                           add_sep_tab
 *========================================================================**/
char	**add_sep_tab(char **cmd_tab_sep, t_ast_nde *node)
{
	char	*sep;

	if (node->token == PIPE)
		sep = "|";
	if (node->token == AND)
		sep = "&&";
	if (node->token == OR)
		sep = "||";
	cmd_tab_sep = ft_calloc(2, sizeof(char *));
	cmd_tab_sep[0] = ft_strdup(sep);
	cmd_tab_sep[1] = NULL;
	return (cmd_tab_sep);
}

/**========================================================================
 *                           add_redir_tabs
 *========================================================================**/
char	***add_redir_tabs(char ***cmd_tab, t_ast_nde **node, int *i)
{
	char	*chev;

	if ((*node)->token == SCHEV_LFT)
		chev = "<";
	if ((*node)->token == SCHEV_RGTH)
		chev = ">";
	if ((*node)->token == DCHEV_LFT)
		chev = "<<";
	if ((*node)->token == DCHEV_RGTH)
		chev = ">>";
	cmd_tab[*i] = ft_calloc(3, sizeof(char *));
	cmd_tab[*i][0] = ft_strdup(chev);
	cmd_tab[*i][1] = get_node_str((*node)->sibling->child);
	cmd_tab[*i][2] = NULL;
	(*node)->sibling->token = CMD;
	(*i)++;
	return (cmd_tab);
}

/**========================================================================
 *                           add_remaining_tabs
 *========================================================================**/
char	**add_remaining_tabs(char **cmd_tab_tab, t_ast_nde *node)
{
	int	nbr;
	int	i;

	nbr = get_cmd_nbr(node);
	cmd_tab_tab = ft_calloc(nbr + 1, sizeof(char *));
	cmd_tab_tab[nbr] = NULL;
	i = 0;
	while (!is_separator(node))
	{
		if (node->token == JOKER)
		{
			ft_printf("found JOKER\n");
		}
		if (!is_chevron(node) && node->token != CMD)
			cmd_tab_tab[i++] = get_node_str(node->child);
		node = node->sibling;
	}
	return (cmd_tab_tab);
}

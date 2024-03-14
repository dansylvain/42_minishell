/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_command_tab_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 07:50:04 by dan               #+#    #+#             */
/*   Updated: 2024/03/14 14:02:42 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fill_command_tab_utils.h"
#include "ft_printf.h"
void *ft_realloc(void *ptr, size_t size, size_t old_size);

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

int	get_new_realloc_size(int i, char *wild_str)
{
	int	new_size;
	int	j;

	
	new_size = i;
	j = 0;
	while (wild_str[j])
	{
		if (wild_str[j] == ' ')
			new_size++;
		j++;
	}
	return (new_size + 1);
}


/**========================================================================
 *                           add_remaining_tabs
 *========================================================================**/
char	**add_remaining_tabs(char **cmd_tab_tab, t_ast_nde *node)
{
	int	nbr;
	int	i;
	int new_size;
	
	nbr = get_cmd_nbr(node);
	cmd_tab_tab = ft_calloc(nbr + 1, sizeof(char *));
	cmd_tab_tab[nbr] = NULL;
	i = 0;
	while (!is_separator(node))
	{
		if (node->token == JOKER)
		{
			// count realloc size
			ft_printf("i: %i, nbr: %i\n", i, nbr);
			// use i as the index where to start adding new strs
			new_size = get_new_realloc_size(i, node->start);
			ft_printf("new_size: %i\n", new_size);
			
			cmd_tab_tab = ft_realloc(cmd_tab_tab, (new_size + 1) * sizeof(char *), i * sizeof(char *));
			// realloc ptr (NULL terminated)
			// split wildcard_str in str tab
			// add str tb strs to cmd_tab
			
			ft_printf("found JOKER\n");
		}
		if (!is_chevron(node) && node->token != CMD)
			cmd_tab_tab[i++] = get_node_str(node->child);
		node = node->sibling;
	}
	return (cmd_tab_tab);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_command_tab_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 07:50:04 by dan               #+#    #+#             */
/*   Updated: 2024/03/14 13:12:55 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fill_command_tab_utils.h"
#include "ft_printf.h"
#include "libft.h"
void	*ft_realloc(void *ptr, size_t size);

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

int	get_new_ptr_size(int i, char *wild_str)
{
	int j;
	
	j = 0;
	while (wild_str[j])
	{
		if (wild_str[j] == ' ')
			i++;
		j++;
	}
	return (i + 1);
}

/**========================================================================
 *                           add_remaining_tabs
 *========================================================================**/
char	**add_remaining_tabs(char **cmd_tab_tab, t_ast_nde *node)
{
	int	nbr;
	int	i;

	nbr = get_cmd_nbr(node);
	ft_printf("nbr = %i\n", nbr);
	cmd_tab_tab = ft_calloc(nbr + 1, sizeof(char *));
	cmd_tab_tab[nbr] = NULL;
	i = 0;
	while (!is_separator(node))
	{
		if (node->token == JOKER)
		{
			nbr = get_new_ptr_size(i, node->start);
			ft_printf("i: %i, new nbr: %i\n", i, nbr);
			// i = index of first to be added string
			// nbr = total number of strings

			cmd_tab_tab = ft_realloc(cmd_tab_tab, (nbr + 1) * sizeof(char *));
			cmd_tab_tab[nbr] = NULL;
			
			// realloc **
			// add strings & increment i
			ft_printf("DO SOMETHING HERE\n");
		}
		if (!is_chevron(node) && node->token != CMD)
			cmd_tab_tab[i++] = get_node_str(node->child);
		node = node->sibling;
	}
	return (cmd_tab_tab);
}

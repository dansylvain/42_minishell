/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_command_tab_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 17:38:25 by seblin            #+#    #+#             */
/*   Updated: 2024/03/10 16:25:18 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fill_command_tab_utils.h"

int	is_raw(t_ast_nde *node)
{
	if (node->token == RAW)
		return (1);
	return (0);
}

void	add_pipe_tab_to_tab(char ****cmd_tab, int *i)
{
	int	j;
	j = 0;
	while ((*cmd_tab)[*i][j] && (*cmd_tab)[*i][j][0])
		j++;
	(*cmd_tab)[*i][j] = NULL;
//printf("hello im add pipe to tab and looking for my segfaut did you see?\n");
	if ((*cmd_tab)[*i][0][0])
		(*i)++;
//printf("hello im after add pipe to tab and looking for my segfaut did you see?\n");
	(*cmd_tab)[*i][0][0] = '|';
	(*cmd_tab)[*i][0][1] = '\0';
	(*cmd_tab)[*i][1] = NULL;
	(*i)++;
}

void	create_chev_tab(char ****cmd_tab, t_ast_nde **current, int *i)
{
	char	*chev;

	if ((*cmd_tab)[*i][0][0])
		(*i)++;
	if ((*current)->token == SCHEV_LFT)
		chev = "<";
	if ((*current)->token == SCHEV_RGTH)
		chev = ">";
	if ((*current)->token == DCHEV_LFT)
		chev = "<<";
	if ((*current)->token == DCHEV_RGTH)
		chev = ">>";
	(*current)->sibling->token = CHEV_FILE;
	ft_memcpy(&(*cmd_tab)[*i][0][0], chev, ft_strlen(chev));
	ft_memcpy(&(*cmd_tab)[*i][1][0], (*current)->sibling->child->start,
		(*current)->sibling->child->end
		- (*current)->sibling->child->start + 1);
	(*cmd_tab)[*i][2] = NULL;
	(*i)++;
}

void	add_raw_to_cmd_tab(t_Data *data, char ****cmd_tab,
		t_ast_nde *current, int *i)
{
	int	j;

	j = 0;
	while ((*cmd_tab)[*i][j] && (*cmd_tab)[*i][j][0])
		j++;
	(*cmd_tab)[*i][j] = get_node_str(data, current->child);
}

void	complete_raw_tab(t_Data *data, char ****cmd_tab,
		t_ast_nde *node, int *i)
{
	t_ast_nde	*current;
	int			j;

	j = 0;
	while ((*cmd_tab)[*i - 1][j] && (*cmd_tab)[*i - 1][j][0])
		j++;
	current = node->child->sibling;
	ft_strcat((*cmd_tab)[*i - 1][j - 1], get_node_str(data, current));
}

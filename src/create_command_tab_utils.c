/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command_tab_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:53:57 by dan               #+#    #+#             */
/*   Updated: 2024/03/06 09:03:25 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
 *                           is_pipeline
 *========================================================================**/
int	is_pipeline(t_ast_nde *cmd_tab_node_sav)
{
	while (cmd_tab_node_sav)
	{
		if (cmd_tab_node_sav->token == PIPE || cmd_tab_node_sav->token
			== DCHEV_RGTH || cmd_tab_node_sav->token == SCHEV_RGTH)
			return (1);
		cmd_tab_node_sav = cmd_tab_node_sav->sibling;
	}
	return (0);
}

/**========================================================================
 *                           get_node_str
 *========================================================================**/
char	*get_node_str(t_Data *data, t_ast_nde *node)
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

/**========================================================================
 *                           get_cmd_nbr
 *========================================================================**/
int	get_cmd_nbr(t_ast_nde *node)
{
	int	cmd_nbr;

	cmd_nbr = 1;
	while (node)
	{
		if (is_chevron(node))
		{
			cmd_nbr++;
			if (node->sibling->sibling)
				node = node->sibling->sibling;
			else
				break ;
			continue ;
		}
		if (node->token == PIPE)
			cmd_nbr += 2;
		node = node->sibling;
	}
	// ft_printf("cmd_nbr: %i\n", cmd_nbr);
	return (cmd_nbr);
}

void	display_command_tab(char **command_tab)
{
	int	i;

	i = 0;
	ft_printf("command_tab: \n");
	while (command_tab[i])
	{
		ft_printf("cmd_tab[%i]: >%s<\n", i, command_tab[i]);
		i++;
	}
}

void	display_command_tab_big(char ***command_tab)
{
	int	i;
	int	j;

	i = 0;
	ft_printf("command_tab: \n");
	while (command_tab[i])
	{
		j = 0;
		while (command_tab[i][j])
		{
			ft_printf("cmd_tab[%i][%i]: >%s<\n", i, j, command_tab[i][j]);
			j++;
		}
		i++;
	}
}
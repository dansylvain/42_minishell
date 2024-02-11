/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 19:55:38 by dan               #+#    #+#             */
/*   Updated: 2024/02/11 20:26:32 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "parsing_utils.h"

int	check_if_env_var_and_get_it(t_Data *data, t_ast_nde *node, char str[], int index)
{
	int	i;
	
	i = 0;
	if (node->token == RAW || node->token == IN_DQUTE)
	{
		
	}
}
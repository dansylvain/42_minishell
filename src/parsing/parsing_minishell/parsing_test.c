/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 14:43:41 by svidot            #+#    #+#             */
/*   Updated: 2024/02/05 15:31:36 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_utils.h"
#include "ft_printf.h"

void	print_sib(t_ast_nde *sib)
{
	int	i;	
	int	back_color;
	const t_ast_nde *sib_sav;
	t_ast_nde *sib_sav2;
	
	back_color = 41; 
	sib_sav2 = sib;	
	ft_printf("\n");
	while (sib)
	{	
		sib_sav = sib;
		while (sib && sib->token == 0)
		{	
			i = 0;
			while (sib->start + i <= sib->end)
				ft_printf("\033[%dm%c\033[0m", back_color, sib->start[i++]);
			back_color = (back_color - 41 + 1) % 7 + 41;
			sib = sib->sibling;
		}
		//ft_printf("\n");
		if (sib_sav && sib_sav->token == PIPE)
		{	
			t_ast_nde *tmp = sib_sav->child->child;
			while (tmp)
			{	
				i = 0;
				while (tmp->start + i <= tmp->end)
					ft_printf("\033[%dm%c\033[0m", back_color, tmp->start[i++]);
				back_color = (back_color - 41 + 1) % 7 + 41;	
				tmp = tmp->sibling;				
			}
			tmp = sib_sav->child->sibling->child;
			while (tmp)
			{	
				i = 0;
				while (tmp->start + i <= tmp->end)
					ft_printf("\033[%dm%c\033[0m", back_color, tmp->start[i++]);
				back_color = (back_color - 41 + 1) % 7 + 41;	
				tmp = tmp->sibling;				
			}
			//ft_printf("\n");
		}		
		ft_printf("\n");
		sib = sib_sav->child;		
	}
	ft_printf("\n");
}

void	print_qute_sib(t_ast_nde *sib)
{
	int	i;	
	int	back_color;
	
	while (sib)
	{
		if (sib->token == RAW)				
			back_color = 41;		
		else if (sib->token == SQUTE)	
			back_color = 40;
		else if (sib->token == IN_SQUTE)	
			back_color = 42;		
		else if (sib->token == DQUTE)		
			back_color = 45;
		else if (sib->token == IN_DQUTE)	
			back_color = 46;	
		i = 0;
		while (sib->start + i <= sib->end)
			ft_printf("\033[%dm%c\033[0m", back_color, sib->start[i++]);
		sib = sib->sibling;
	}
	ft_printf("\n");
}
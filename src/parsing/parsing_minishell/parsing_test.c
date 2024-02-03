/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 14:43:41 by svidot            #+#    #+#             */
/*   Updated: 2024/02/03 16:03:49 by svidot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_utils.h"
#include "ft_printf.h"
void	print_sib42(t_ast_nde *sib)
{
	int	i;	
	int	back_color;
	const t_ast_nde *sib_sav;
	t_ast_nde *sib_sav2;
		printf("deb\n");
	back_color = 41; 
	sib_sav2 = sib;	
	while (sib)
	{	
		sib_sav = sib;
		while (sib)
		{	
			i = 0;
			while (sib->start + i <= sib->end)
				printf("\033[%dm%c\033[0m", back_color, sib->start[i++]);
			back_color = (back_color - 41 + 1) % 7 + 41;
			sib = sib->sibling;
		}
		if (sib_sav && sib_sav->token == PIPE)
		{
			printf("right\n");
			t_ast_nde *tmp = sib_sav->child->sibling->child;
			while (tmp)
			{	
				i = 0;
				while (tmp->start + i <= tmp->end)
					printf("\033[%dm%c\033[0m", back_color, tmp->start[i++]);
				back_color = (back_color - 41 + 1) % 7 + 41;	
				tmp = tmp->sibling;				
			}
			printf("\n");
		}		
		sib = sib_sav->child;
		
		printf("f\n");
	}
	printf("\n");
	// sib = sib_sav2;
	// while (sib)
	// {	
	// 	sib_sav2 = sib;
	// 	while (sib)
	// 	{	
	// 		i = 0;
	// 		while (sib->start + i <= sib->end)
	// 			printf("\033[%dm%c\033[0m", back_color, sib->start[i++]);
	// 		back_color = (back_color - 41 + 1) % 7 + 41;	
	// 		sib = sib->sibling;
	// 	}
	// 	//if (sib_sav2->child)
	// 	sib = sib_sav2->child;
	// 	printf("f\n");
	// }
}
void	print_sib(t_ast_nde *sib)
{
	int	i;	
	int	back_color;
	const t_ast_nde *sib_sav;
	t_ast_nde *sib_sav2;
	
	back_color = 41; 
	sib_sav2 = sib;	
	while (sib)
	{	
		sib_sav = sib;
		while (sib)
		{	
			i = 0;
			while (sib->start + i <= sib->end)
				ft_printf("\033[%dm%c\033[0m", back_color, sib->start[i++]);
			back_color = (back_color - 41 + 1) % 7 + 41;
			sib = sib->sibling;
		}
		if (sib_sav && sib_sav->token == PIPE)
		{	
			t_ast_nde *tmp = sib_sav->child->sibling->child;
			while (tmp)
			{	
				i = 0;
				while (tmp->start + i <= tmp->end)
					ft_printf("\033[%dm%c\033[0m", back_color, tmp->start[i++]);
				back_color = (back_color - 41 + 1) % 7 + 41;	
				tmp = tmp->sibling;				
			}
			ft_printf("\n");
		}		
		sib = sib_sav->child;		
		ft_printf("\n");
	}
	ft_printf("\n");
}

void	print_qute_sib(t_ast_nde *sib)
{
	int	i;	
	int	back_color;
	
	while (sib)
	{
		if (sib->token == NONE)				
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
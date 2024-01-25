/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 15:41:31 by dan               #+#    #+#             */
/*   Updated: 2024/01/22 16:01:07 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	sigint_handler(int signum);
static void	sigquit_handler(int signum);

/**========================================================================
 *                           handle_signals
 *========================================================================**/
void	handle_signals(void)
{
	signal(2, sigint_handler);
	signal(3, sigquit_handler);
}

/**========================================================================
 *                           sigint_handler
 *========================================================================**/
static void	sigint_handler(int signum)
{
	(void)signum;
	ft_printf("^C\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/**========================================================================
 *                           sigkill_handler
 *========================================================================**/
static void	sigquit_handler(int signum)
{
	(void)signum;
}

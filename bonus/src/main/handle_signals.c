/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 15:41:31 by dan               #+#    #+#             */
/*   Updated: 2024/03/08 14:46:54 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "handle_signals.h"

/**========================================================================
 *                           handle_signals
 * 2 => SIGINT (CTRL + C)
 * 3 => SIGQUIT (CTRL + \)
 *========================================================================**/
void	handle_signals(void)
{
	signal(2, sigint_handler);
	signal(3, sigquit_handler);
}

/**========================================================================
 *                           sigint_handler
 * replaces the content of reasline buffer + displays the prompt anew 
 * waitpid used to check that no other instance of minishell is running
 *========================================================================**/
void	sigint_handler(int signum)
{
	(void)signum;
	if (waitpid(-1, NULL, WNOHANG) == -1)
	{
		ft_printf("^C\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

/**========================================================================
 *                           sigkill_handler
 * does nothing... as expected
 *========================================================================**/
void	sigquit_handler(int signum)
{
	(void)signum;
}

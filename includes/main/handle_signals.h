#ifndef HANDLE_SIGNALS_H
#define HANDLE_SIGNALS_H

#include <minishell_struct.h>
#include "rl_header.h"
#include <signal.h>
#include <sys/wait.h>
#include "ft_printf.h"

void	handle_signals(void);
void	sigint_handler(int signum);
void	sigquit_handler(int signum);

#endif

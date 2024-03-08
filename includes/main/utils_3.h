#ifndef UTILS_3_H
#define UTILS_3_H

#include <minishell_struct.h>
#include <stdlib.h>
#include <libft.h>
#include "ft_printf.h"

void	update_shlvl(char	**envp_tab);
void	free_command_tab(char ***command_tab);

#endif

#ifndef EXEC_UNSET_H
#define EXEC_UNSET_H

#include <minishell_struct.h>
#include <stdlib.h>
#include "libft.h"

void	exec_unset(t_Data *data, char **command_tab);
void	unset_var(char **envp, int index);

#endif

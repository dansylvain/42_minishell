#ifndef UTILS_2_H
#define UTILS_2_H

#include <minishell_struct.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "libft.h"

void	display_error(char *str);
void	display_error_free(char *str);
void	display_error_detail(char *str, char *details, char *str2);

#endif

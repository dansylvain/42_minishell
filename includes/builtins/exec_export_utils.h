#ifndef EXEC_EXPORT_UTILS_H
#define EXEC_EXPORT_UTILS_H

#include <minishell_struct.h>
#include "ft_printf.h"
#include "libft.h"

void	create_export_tab(t_Data *data, char export_tab[][500]);
void	format_export_tab(char export_tab[][500]);
void	insert_quote(char *str);
int		has_var(char *str);
void	display_export_tab(char export_tab[][500]);

#endif

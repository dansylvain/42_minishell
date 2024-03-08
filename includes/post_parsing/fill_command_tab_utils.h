/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_command_tab_utils.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 20:35:21 by dan               #+#    #+#             */
/*   Updated: 2024/03/08 20:40:12 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILL_COMMAND_TAB_UTILS_H
# define FILL_COMMAND_TAB_UTILS_H

# include "minishell.h"
# include "parsing_utils.h"
# include <stddef.h>
# include "libft.h"

char	*get_node_str(t_Data *data, t_ast_nde *node);

#endif

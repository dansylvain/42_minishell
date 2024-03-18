/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leaf_par.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 11:13:57 by seblin            #+#    #+#             */
/*   Updated: 2024/03/18 15:10:37 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEAF_PAR_H
# define LEAF_PAR_H

# include "parsing_utils.h"
# include "minishell.h"
# include "libft.h"
# include <stdlib.h>

int	exec_pipex(t_Data *data, char *cmd, char *envp[], int reset);
int	raw_left_area(t_ast_nde *raw_lft, t_Data *data, int *or_flag);
int	middle_area(t_ast_nde *middle, t_Data *data, int or_flag);
int	raw_right_area(t_ast_nde *raw_rght, t_Data *data);
int	*get_err_policy(void);

#endif
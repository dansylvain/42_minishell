/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leaf_par_raw.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 11:14:01 by seblin            #+#    #+#             */
/*   Updated: 2024/03/18 15:10:58 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEAF_PAR_RAW_H
# define LEAF_PAR_RAW_H

# include "parsing_utils.h"
# include "minishell.h"
# include "libft.h"
# include <stdlib.h>

int	exec_pipex(t_Data *data, char *cmd, char *envp[], int reset);
int	leaf_tree_par(t_ast_nde	*raw, t_Data *data);
int	parse_par(char *str, t_Data *data, t_ast_nde *root);
int	*get_err_policy(void);

#endif
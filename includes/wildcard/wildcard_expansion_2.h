/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expansion_2.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 19:10:36 by dan               #+#    #+#             */
/*   Updated: 2024/03/08 19:42:28 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARD_EXPANSION_2_H
# define WILDCARD_EXPANSION_2_H

# include <minishell.h>
# include <stdlib.h>
# include <dirent.h>
# include <stdio.h>
# include "libft.h"

int	matches_pattern(const char *filename, const char *pattern);

#endif

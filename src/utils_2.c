/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:09:48 by dan               #+#    #+#             */
/*   Updated: 2024/02/20 11:12:47 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**========================================================================
 *                           display_error
 * takes the error message as argument
 *! error message should not be longer than 1000 chars
*========================================================================**/
void	display_error(char *str)
{
	if (write(2, str, ft_strlen(str)) == -1)
		perror("display_error");
}

/**========================================================================
 *                       display_error_detail
 *========================================================================**/
void	display_error_detail(char *str, char *details, char *str2)
{
	char	tmp[2000];
	int		len;
	int		len1;
	int		len2;
	int		len3;

	len = 0;
	ft_bzero(tmp, 2000);
	len1 = ft_strlen(str);
	memcpy(tmp, str, len1);
	len += len1;
	len2 = ft_strlen(details);
	memcpy(&tmp[len + 1], details, len2);
	len += len2 + 1;
	len3 = ft_strlen(str2);
	memcpy(&tmp[len + 1], str2, len3);
	len += len3 + 1;
	if (write(2, tmp, len) == -1)
		perror("display_error");
}

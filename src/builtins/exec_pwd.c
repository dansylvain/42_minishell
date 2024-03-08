/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 19:12:50 by dan               #+#    #+#             */
/*   Updated: 2024/03/08 16:24:03 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_pwd.h"

/**========================================================================
 *                           exec_pwd
 *========================================================================**/
void	exec_pwd(t_Data *data)
{
	char	buffer[1024];

	if (getcwd(buffer, sizeof(buffer)) != NULL)
		ft_printf("%s\n", buffer);
	else
		perror("getcwd");
	(void)data;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 19:12:50 by dan               #+#    #+#             */
/*   Updated: 2024/02/13 16:57:53 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h>
void	exec_pwd(t_Data *data)
{
	char	buffer[1024];
write(2, "IN EXC pwd!\n", 13);
	if (getcwd(buffer, sizeof(buffer)) != NULL)
	{
		printf("%s\n", buffer);
	}
	else
	{
		perror("getcwd");
	}
	//exit(0);
}

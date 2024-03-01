/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 11:22:17 by dan               #+#    #+#             */
/*   Updated: 2024/03/01 18:25:29 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t size)
{
	void	*new_ptr;
				
	new_ptr = (void *) malloc(size);
	if (!new_ptr)
		return (NULL);
	if (ptr && size > 0)
		ft_memcpy(new_ptr, ptr, size);
	free(ptr);
	return (new_ptr);
}

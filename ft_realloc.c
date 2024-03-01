/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 12:39:21 by seblin            #+#    #+#             */
/*   Updated: 2023/09/28 21:59:43 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
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
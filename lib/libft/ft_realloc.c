/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 11:22:17 by dan               #+#    #+#             */
/*   Updated: 2024/02/18 11:35:52 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void *ft_realloc(void *ptr, size_t size)
{
	if (ptr == NULL)
		return malloc(size);
	if (size == 0)
		return (free(ptr), NULL);
	void *new_ptr = malloc(size);
	if (new_ptr == NULL)
		return NULL;
	if (ptr && size > 0)
		ft_memcpy(new_ptr, ptr, size);
	free(ptr);
	return new_ptr;
}

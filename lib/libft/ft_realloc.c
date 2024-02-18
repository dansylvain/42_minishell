/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 11:22:17 by dan               #+#    #+#             */
/*   Updated: 2024/02/18 11:27:30 by dan              ###   ########.fr       */
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
	size_t old_size = sizeof(ptr);
	ft_memcpy(new_ptr, ptr, old_size);
	free(ptr);
	return new_ptr;
}

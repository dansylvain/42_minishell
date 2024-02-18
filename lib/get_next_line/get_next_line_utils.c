/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 10:00:32 by dan               #+#    #+#             */
/*   Updated: 2024/02/18 17:05:06 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*delete_data(t_gnl **head, int fd)
{
	t_gnl	*current;
	t_gnl	*node_to_delete;

	node_to_delete = NULL;
	current = *head;
	if (current->fd == fd)
	{
		*head = current->next;
		node_to_delete = current;
	}
	else
	{
		while (current->next)
		{
			if (current->next->fd == fd)
			{
				node_to_delete = current->next;
				current->next = current->next->next;
				break ;
			}
			current = current->next;
		}
	}
	delete_node(node_to_delete);
	return (NULL);
}

void	*delete_node(t_gnl *node_to_delete)
{
	if (node_to_delete)
	{
		free(node_to_delete->buff_nl);
		free(node_to_delete->buffer);
		node_to_delete->buff_nl = NULL;
		node_to_delete->buffer = NULL;
		free(node_to_delete);
		node_to_delete = NULL;
	}
	return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;

	if ((start + len) > ft_strlen_gnl(s))
		substr = (char *)malloc(sizeof(char) * (ft_strlen_gnl(s) - start + 1));
	else
		substr = (char *)malloc(sizeof(char) * len + 1);
	if (substr == NULL)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)(s));
		s++;
	}
	if ((char)c == '\0')
		return ((char *)(s));
	return (NULL);
}

size_t	ft_strlen_gnl(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

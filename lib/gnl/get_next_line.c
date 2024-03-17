/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 13:29:55 by svidot            #+#    #+#             */
/*   Updated: 2024/03/12 15:21:45 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

static char	*manage_endfile(char **buffer, char *ext)
{
	char		*line;

	free(ext);
	if (**buffer)
	{
		line = ft_strndup_gnl(*buffer, ft_strlen_gnl(*buffer));
		if (!line)
			return (free_buffer_gnl(buffer));
		(*buffer)[0] = '\0';
		return (line);
	}
	else
		return (free_buffer_gnl(buffer));
}

static char	*manage_prequel(char **buffer)
{
	if (!*buffer)
	{
		*buffer = (char *) ft_calloc_gnl(1, sizeof(char));
		if (!*buffer)
			return (NULL);
	}
	return ("ok");
}

static char	*merge_buffers(char **buffer, char *ext)
{
	char	*new_buff;
	size_t	buffer_len;
	size_t	ext_len;

	buffer_len = ft_strlen_gnl(*buffer);
	ext_len = ft_strlen_gnl(ext);
	new_buff = (char *) malloc((buffer_len + ext_len + 1) * sizeof (char));
	if (!new_buff)
	{
		free(ext);
		return (free_buffer_gnl(buffer));
	}
	while (**buffer)
		*new_buff++ = *(*buffer)++;
	while (*ext)
		*new_buff++ = *ext++;
	*new_buff = '\0';
	*buffer -= buffer_len;
	free(*buffer);
	free(ext - ext_len);
	*buffer = new_buff - ext_len - buffer_len;
	return ("ok");
}

static char	*manage_no_newline(int fd, char **buffer, char **newline)
{
	char		*ext;
	ssize_t		read_size;

	while (!*newline)
	{
		ext = (char *) ft_calloc_gnl(BUFFER_SIZE + 1, sizeof(char));
		if (!ext)
			return (free_buffer_gnl(buffer));
		read_size = read(fd, ext, BUFFER_SIZE);
		if (read_size > 0)
		{
			if (!merge_buffers(buffer, ext))
				return (NULL);
			*newline = ft_strchr_gnl(*buffer, '\n');
		}
		else if (read_size == 0)
			return (manage_endfile(buffer, ext));
		else
		{
			free(ext);
			return (free_buffer_gnl(buffer));
		}
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*buffer;	
	char		*newline;
	char		*line;
	char		*rslt_nonewl;
	size_t		newline_len;

	if (!manage_prequel(&buffer))
		return (NULL);
	newline = ft_strchr_gnl(buffer, '\n');
	if (!newline)
	{
		rslt_nonewl = manage_no_newline(fd, &buffer, &newline);
		if ((!rslt_nonewl && !newline) || rslt_nonewl)
			return (rslt_nonewl);
	}
	line = ft_strndup_gnl(buffer, ++newline - buffer);
	if (!line)
		return (free_buffer_gnl(&buffer));
	newline_len = ft_strlen_gnl(newline);
	while (*newline)
		*buffer++ = *newline++;
	*buffer = '\0';
	buffer -= newline_len;
	return (line);
}

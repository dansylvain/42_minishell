/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 09:57:00 by dsylvain          #+#    #+#             */
/*   Updated: 2024/02/18 17:03:05 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_gnl	*head = NULL;
	t_gnl			*data;
	char			*next_line;
	char			*tmp;

	data = get_data(&head, fd);
	if (!initialise_variables(&data) || !data)
		return (delete_data(&data, fd));
	while (!(ft_strchr(data->buff_nl, '\n')) && data->bytes_read)
	{
		data->bytes_read = read(fd, data->buffer, BUFF);
		if (data->bytes_read == -1)
			return (delete_data(&head, fd));
		data->buffer[data->bytes_read] = '\0';
		data->buff_nl = expand_buff_nl(&data);
		if (!data->buff_nl)
			return (delete_data(&data, fd));
	}
	tmp = ft_strchr(data->buff_nl, '\n');
	next_line = build_next_line(&data, tmp, data->bytes_read);
	if (next_line)
		return (next_line);
	delete_data(&head, fd);
	return (NULL);
}

t_gnl	*get_data(t_gnl **head, int fd)
{
	t_gnl	*current;

	current = *head;
	while (current)
	{
		if (current->fd == fd)
			return (current);
		current = current->next;
	}
	current = (t_gnl *)malloc(sizeof(t_gnl));
	if (!current)
		return (delete_node(current));
	current->buff_nl = NULL;
	current->buffer = NULL;
	current->fd = fd;
	current->next = *head;
	*head = current;
	return (current);
}

int	initialise_variables(t_gnl **data)
{
	size_t			i;

	if (!(*data)->buff_nl)
	{
		(*data)->buff_nl = (char *)malloc((BUFF * 5) * sizeof(char));
		(*data)->buff_nl_size = BUFF * 5;
		i = 0;
		while (i < BUFF * 5)
			(*data)->buff_nl[i++] = '\0';
	}
	if (!(*data)->buffer)
	{
		i = 0;
		(*data)->buffer = (char *)malloc((BUFF + 1) * sizeof(char));
		while (i < BUFF + 1)
			((*data)->buffer)[i++] = '\0';
	}
	if (!*data || !(*data)->buff_nl || !(*data)->buffer)
	{
		delete_node(*data);
		return (0);
	}
	(*data)->bytes_read = 1;
	return (1);
}

void	*expand_buff_nl(t_gnl **data)
{
	char	*tmp;
	size_t	i;
	size_t	j;

	tmp = NULL;
	i = 0;
	if (((*data)->buff_nl_size - ft_strlen_gnl((*data)->buff_nl) < BUFF + 1))
	{
		tmp = (*data)->buff_nl;
		(*data)->buff_nl = (char *)malloc((*data)->buff_nl_size * 2);
		if (!(*data)->buff_nl)
			return (delete_node(*data));
		(*data)->buff_nl_size *= 2;
		while (*tmp)
			(*data)->buff_nl[i++] = *tmp++;
		free(tmp - i);
	}
	if (i == 0)
		i = ft_strlen_gnl((*data)->buff_nl);
	j = 0;
	while (j < ft_strlen_gnl((*data)->buffer))
		(*data)->buff_nl[i++] = (*data)->buffer[j++];
	while (i < (size_t)(*data)->buff_nl_size)
		(*data)->buff_nl[i++] = '\0';
	return ((*data)->buff_nl);
}

char	*build_next_line(t_gnl **data, char *tmp, int bytes_read)
{
	char	*next_line;
	size_t	i;

	if (tmp)
	{
		next_line = ft_substr((*data)->buff_nl, 0, tmp - (*data)->buff_nl + 1);
		if (!(*data)->buff_nl)
			return (delete_node(*data));
		i = 0;
		while (i < ft_strlen_gnl(tmp) - 1 && (tmp + 1)[i] != '\0')
		{
			((*data)->buff_nl)[i] = (tmp + 1)[i];
			i++;
		}
		((*data)->buff_nl)[i] = '\0';
		return (next_line);
	}
	else if (bytes_read == 0 && *(*data)->buff_nl)
	{
		next_line = ft_substr((*data)->buff_nl, 0,
				ft_strlen_gnl((*data)->buff_nl));
		*(*data)->buff_nl = '\0';
		return (next_line);
	}
	return (NULL);
}

// #include <unistd.h>
// int main(void)
// {
// 	int	fd1;
// 	int	fd2;
// 	int	fd3;
// 	char *str1;
// 	char *str2;
// 	char *str3;
// 	str1 = "";
// 	str2 = "";
// 	str3 = "";
// 	fd1 = open("text1.txt", O_RDONLY);
// 	fd2 = open("text2.txt", O_RDONLY);
// 	fd3 = open("text3.txt", O_RDONLY);
// 	while(str1 || str2)
// 	{
// 		str1 = get_next_line(fd1);
// 		if (str1)
// 		{
// 			write(1, "fd1: ", 5);
// 			write(1, &*str1, ft_strlen(str1));
// 		}
// 		str2 = get_next_line(fd2);
// 		if (str2)
// 		{
// 			write(1, "fd2: ", 5);
// 			write(1, &*str2, ft_strlen(str2));
// 		}
// 		str3 = get_next_line(fd3);
// 		if (str3)
// 		{
// 			write(1, "fd3: ", 5);
// 			write(1, &*str3, ft_strlen(str3));
// 		}
// 	}
// 	return(0);
// }
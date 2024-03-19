/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:15:30 by svidot            #+#    #+#             */
/*   Updated: 2024/03/12 15:17:55 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <stdlib.h>

char	*get_next_line(int fd);
size_t	ft_strlen_gnl(const char *s);
char	*ft_strcpy_gnl(char *dest, const char *src);
char	*ft_strndup_gnl(const char *s, size_t n);
char	*ft_strchr_gnl(const char *s, int c);
void	*free_buffer_gnl(char **buffer);
void	*ft_calloc_gnl(size_t nmemb, size_t size);

#endif
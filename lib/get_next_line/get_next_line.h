/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 04:58:59 by dsylvain          #+#    #+#             */
/*   Updated: 2024/02/18 17:03:09 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFF
#  define BUFF 42
# endif

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct t_gnl
{
	char			*buff_nl;
	char			*buffer;
	int				bytes_read;
	int				buff_nl_size;
	int				fd;
	struct t_gnl	*next;
}	t_gnl;

char	*get_next_line(int fd);
t_gnl	*get_data(t_gnl **head, int fd);
int		initialise_variables(t_gnl **data);
void	*expand_buff_nl(t_gnl **data);
char	*build_next_line(t_gnl **data, char *tmp, int bytes_read);
void	*delete_data(t_gnl **head, int fd);
void	*delete_node(t_gnl *node_to_delete);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlen_gnl(const char *s);

#endif

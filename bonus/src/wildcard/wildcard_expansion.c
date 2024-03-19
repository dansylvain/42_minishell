/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsylvain <dsylvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 10:14:43 by dan               #+#    #+#             */
/*   Updated: 2024/03/19 13:08:35 by dsylvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard_expansion.h"

/**========================================================================
 *                           wildcard_func
 *========================================================================**/
char	*wildcard_func(char *pattern)
{
	size_t	i;
	char	**matches;
	char	*ret_str;
	int		index;

	index = 0;
	if (!ft_strchr(pattern, '*'))
		return (NULL);
	matches = expand_wildcards(pattern);
	if (matches == NULL || matches[0] == NULL)
		return (pattern);
	ret_str = (char *)ft_calloc(get_str_size(matches), sizeof(char) + 1);
	if (ret_str == NULL)
	{
		i = 0;
		while (matches[i])
			free(matches[i++]);
		return (free(matches), NULL);
	}
	if (matches[0] != NULL)
		return (copy_matches(&matches, &ret_str, index, &pattern));
	i = 0;
	while (matches[i])
		free(matches[i++]);
	return (free(matches), NULL);
}

/**========================================================================
 *                           expand_wildcards
 *========================================================================**/
char	**expand_wildcards(const char *pattern)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**matches;
	size_t			count;

	entry = NULL;
	matches = NULL;
	count = 0;
	dir = opendir(".");
	if ((dir) != NULL)
	{
		count = get_matching_elements(pattern, dir, entry, &matches);
	}
	else
	{
		perror("opendir");
		exit(EXIT_FAILURE);
	}
	return (matches);
	(void)count;
}

/**========================================================================
 *                           get_str_size
 *========================================================================**/
int	get_str_size(char **matches)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (matches[i])
	{
		res += ft_strlen(matches[i]) + 1;
		i++;
	}
	res -= 1;
	return (res);
}

/**========================================================================
 *                           copy_matches
 *========================================================================**/
char	*copy_matches(char ***matches, char **ret_str,
		int index, char **pattern)
{
	int	i;

	i = 0;
	while ((*matches)[i] != NULL)
	{
		ft_memcpy(&(*ret_str)[index], (*matches)[i],
			ft_strlen((*matches)[i]));
		index += ft_strlen((*matches)[i]);
		if ((*matches)[i + 1])
			(*ret_str)[index++] = ' ';
		free((*matches)[i++]);
	}
	free(*pattern);
	return (free (*matches), *ret_str);
}

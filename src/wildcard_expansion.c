/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 10:14:43 by dan               #+#    #+#             */
/*   Updated: 2024/03/02 15:25:03 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	matches_pattern(const char *filename, const char *pattern);

int	get_matching_elements(const char *pattern, DIR *dir,
	struct dirent *entry, char ***matches)
{
	size_t	count;
	
	count = 0;
	while (1)
	{
		entry = readdir(dir);
		if (entry == NULL)
			break ;
		if (matches_pattern(entry->d_name, pattern))
		{
			*matches = ft_realloc(*matches, (count + 2) * sizeof(char *));
			if (*matches == NULL)
			{
				perror("realloc");
				exit(EXIT_FAILURE);
			}
			(*matches)[count] = ft_strdup(entry->d_name);
			count++;
			(*matches)[count] = NULL;
			int i = 0;
		}
	}
	closedir(dir);
	return (count);
}

	char	**expand_wildcards(const char *pattern)
	{
		DIR				*dir;
		struct dirent	*entry = NULL;
		char			**matches;
		size_t			count;

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
	}

int	matches_pattern(const char *filename, const char *pattern)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < ft_strlen(filename) && j < ft_strlen(pattern))
	{
		if (pattern[j] == '*')
		{
			if (pattern[j + 1] == '\0')
				return (1);
			while (i < ft_strlen(filename) && filename[i] != pattern[j + 1])
				i++;
			j++;
		}
		else
		{
			if (filename[i++] != pattern[j++])
				return (0);
		}
	}
	return (i == ft_strlen(filename) && j == ft_strlen(pattern));
}

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
void	copy_matches_to_ret_str(char ***matches, char **ret_str, int index, char **pattern)
{
	int	i;
	
	i = 0;
	while ((*matches)[i] != NULL)
		{
			ft_memcpy(&(*ret_str)[index], (*matches)[i], ft_strlen((*matches)[i]));
			index += ft_strlen((*matches)[i]);
			if ((*matches)[i + 1])
				(*ret_str)[index++] = ' ';
			free((*matches)[i++]);
		}
		free(*pattern);
}

char	*wilcard_func(char *pattern)
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
		return (free (matches), NULL);
	}
	if (matches[0] != NULL)
	{
		copy_matches_to_ret_str(&matches, &ret_str, index, &pattern);
		return (free (matches), ret_str);
	}
	i = 0;
	while (matches[i])
		free(matches[i++]);
	return(free (matches), NULL);
}

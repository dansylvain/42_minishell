/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 10:14:43 by dan               #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/03/01 20:18:31 by seblin           ###   ########.fr       */
=======
/*   Updated: 2024/03/02 15:42:04 by dan              ###   ########.fr       */
>>>>>>> b5be64f9a2a1147130b870671782c03ce595c81a
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

<<<<<<< HEAD
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
		}
	}
	closedir(dir);
	return (count);
}

char	**expand_wildcards(const char *pattern)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**matches;
	size_t			count;

	matches = NULL;
	count = 0;
	dir = opendir(".");
	if ((dir) != NULL)
		count = get_matching_elements(pattern, dir, entry, &matches);
	else
	{
		perror("opendir");
		exit(EXIT_FAILURE);
	}
	matches = ft_realloc(matches, (count + 1) * sizeof(char *));
	if (matches == NULL)
	{
		perror("realloc");
		exit(EXIT_FAILURE);
	}
	matches[count] = NULL;
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
		res += ft_strlen(matches[i]);
		i++;
	}
	return (res);
}
void	print_cmd(t_ast_nde *cmd);
=======
>>>>>>> b5be64f9a2a1147130b870671782c03ce595c81a
char	*wilcard_func(char *pattern)
{
	size_t	i;
	char	**matches;
	char	*ret_str;
	int		index;

	index = 0;
	if (!ft_strchr(pattern, '*'))
		return (free(pattern), NULL);
	matches = expand_wildcards(pattern);
	if (matches == NULL || matches[0] == NULL)
		return (pattern);
	ret_str = (char *)ft_calloc(get_str_size(matches), sizeof(char) + 1);
	if (ret_str == NULL)
<<<<<<< HEAD
		return (free (matches), free(pattern), NULL);
	if (matches[0] != NULL)
=======
>>>>>>> b5be64f9a2a1147130b870671782c03ce595c81a
	{
		i = 0;
		while (matches[i])
			free(matches[i++]);
<<<<<<< HEAD
		}
		free(pattern);
		return (free (matches), ret_str);
	}	
	return(free (matches), 	free(pattern), NULL);
=======
		return (free(matches), NULL);
	}
	if (matches[0] != NULL)
		return (copy_matches(&matches, &ret_str, index, &pattern));
	i = 0;
	while (matches[i])
		free(matches[i++]);
	return (free(matches), NULL);
}

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
>>>>>>> b5be64f9a2a1147130b870671782c03ce595c81a
}

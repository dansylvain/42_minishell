/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expansion_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 15:36:26 by dan               #+#    #+#             */
/*   Updated: 2024/03/14 16:55:38 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard_expansion_2.h"

/**========================================================================
 *                           matches_pattern 
 *========================================================================**/
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

/**========================================================================
 *                           get_matching_elements 
 *========================================================================**/
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
			*matches = ft_realloc(*matches, (count + 2)
					* sizeof(char *), (count) * sizeof(char *));
			if (*matches == NULL)
			{
				perror("realloc");
				exit(EXIT_FAILURE);
			}
			(*matches)[count] = ft_strdup(entry->d_name);
			count++;
			(*matches)[count] = NULL;
		}
	}
	closedir(dir);
	return (count);
}

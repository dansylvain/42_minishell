/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expansion_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 15:36:26 by dan               #+#    #+#             */
/*   Updated: 2024/03/16 14:23:02 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard_expansion_2.h"

int	check_pattern(const char **f, const char **p,
	const char **last_star, const char **last_match)
{
	if (*(*p) == '?' || *(*p) == *(*f))
	{
		(*f)++;
		(*p)++;
		if (!*(*p))
		{
			return (1);
		}
	}
	else if (*(*p) == '*')
	{
		*last_match = (*f);
		*last_star = (*p);
		(*p)++;
	}
	else
	{
		*p = *last_star + 1;
		*f = ++(*last_match);
	}
	return (0);
}

/**========================================================================
 *                           matches_pattern 
 *========================================================================**/
int	matches_pattern(const char *filename, const char *pattern)
{
	const char	*f;
	const char	*p;
	const char	*last_star;
	const char	*last_match;

	f = filename;
	p = pattern;
	last_star = NULL;
	last_match = NULL;
	while (*f && *p != '*')
	{
		if (*p != '?' && *f != *p)
			return (0);
		f++;
		p++;
	}
	if (!*p)
		return (!*f);
	last_star = p;
	while (*f)
		if (check_pattern(&f, &p, &last_star, &last_match))
			return (1);
	while (*p == '*')
		p++;
	return (!*p);
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

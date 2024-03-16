/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expansion_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 15:36:26 by dan               #+#    #+#             */
/*   Updated: 2024/03/16 14:12:35 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard_expansion_2.h"

void	check_pattern()
{

}

/**========================================================================
 *                           matches_pattern 
 *========================================================================**/
int matches_pattern(const char *filename, const char *pattern)
{
    const char *f = filename;
    const char *p = pattern;
    const char *last_star = NULL;
    const char *last_match = NULL;

    while (*f && *p != '*')
	{
        if (*p != '?' && *f != *p)
            return 0;
        f++;
        p++;
    }
    if (!*p)
        return !*f;
    last_star = p;
    while (*f)
	{
		check_pattern();
        if (*p == '?' || *p == *f)
		{
            f++;
            p++;
            if (!*p) {
                return 1;
            }
        }
		else if (*p == '*')
		{
            last_match = f;
            last_star = p;
            p++;
        }
		else
		{
            p = last_star + 1;
            f = ++last_match;
        }
    }
    while (*p == '*')
        p++;
    return !*p;
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 10:14:43 by dan               #+#    #+#             */
/*   Updated: 2024/02/18 11:40:05 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "parsing_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
int matches_pattern(const char *filename, const char *pattern);

char **expand_wildcards(const char *pattern)
{
	DIR *dir;
	struct dirent *entry;
	char **matches = NULL;
	size_t count = 0;

	if ((dir = opendir(".")) != NULL)
	{
		while ((entry = readdir(dir)) != NULL)
	{
			if (matches_pattern(entry->d_name, pattern))
			{
				matches = ft_realloc(matches, (count + 1) * sizeof(char *));
				if (matches == NULL)
				{
					perror("realloc");
					exit(EXIT_FAILURE);
				}
				matches[count] = strdup(entry->d_name);
				count++;
			}
		}
		closedir(dir);
	}
	else
	{
		perror("opendir");
		exit(EXIT_FAILURE);
	}
	matches = realloc(matches, (count + 1) * sizeof(char *));
	if (matches == NULL)
	{
		perror("realloc");
		exit(EXIT_FAILURE);
	}
	matches[count] = NULL;
	return matches;
}



int matches_pattern(const char *filename, const char *pattern)
{
	size_t filename_len = ft_strlen(filename);
	size_t pattern_len = ft_strlen(pattern);
	size_t i = 0, j = 0;

	while (i < filename_len && j < pattern_len)
	{
		if (pattern[j] == '*')
		{
			if (pattern[j + 1] == '\0') return 1;
			while (i < filename_len && filename[i] != pattern[j + 1]) i++;
			j++;
		}
		else
		{
			if (filename[i] != pattern[j]) return 0;
			i++;
			j++;
		}
	}
	return (i == filename_len && j == pattern_len);
}

int	has_wildcard(char *str)
{
	return (ft_strchr(str, '*') != NULL);
}

int wilcard_func(char *pattern)
{
    char **matches;
	if (!has_wildcard(pattern))
        return EXIT_SUCCESS;
    matches = expand_wildcards(pattern);
    if (matches[0] != NULL)
	{
        for (size_t i = 0; matches[i] != NULL; i++)
		{
            ft_printf("%s\n", matches[i]);
            free(matches[i]);
        }
    }
    free(matches);
}

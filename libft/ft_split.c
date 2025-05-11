/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-mos <hoel-mos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 20:46:46 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/05/02 16:20:41 by hoel-mos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_free(char **strs, int j)
{
	int	i;

	i = 0;
	while (i <= j)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return (NULL);
}

static int	count_word(char const *s, char c)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
		{
			words++;
			while (s[i] != '\0' && s[i] != c)
				i++;
		}
	}
	return (words);
}

static char	**filler(char **strs, char c, char const *s)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	while (s[j] != '\0')
	{
		while (s[j] == c)
			j++;
		if (s[j])
		{
			start = j;
			while (s[j] != c && s[j])
				j++;
			strs[i] = ft_substr(s, start, j - start);
			if (strs[i] == NULL)
				return (ft_free(strs, i));
			i++;
		}
	}
	strs[i] = NULL;
	return (strs);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	int		words;

	if (s == NULL)
		return (NULL);
	words = count_word(s, c);
	strs = (char **)safe_alloc((words + 1) * (sizeof(char *)), 0);
	if (strs == NULL)
		return (NULL);
	return (filler(strs, c, s));
}

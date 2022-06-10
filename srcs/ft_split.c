/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumaison <jumaison@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 16:57:40 by jumaison          #+#    #+#             */
/*   Updated: 2022/06/10 20:26:34 by jumaison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

char	is_separator(char c, char *separators)
{
	int	j;

	j = 0;
	while (separators[j])
	{
		if (c == separators[j])
			return (separators[j]);
		j++;
	}
	return ('\0');
}

char	**ft_free_words(char **tab)
{
	unsigned int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

static unsigned int	ft_countwords(const char *s, char *separators)
{
	unsigned int	i;
	unsigned int	words;
	unsigned int	j;

	if (!s[0])
		return (0);
	i = 0;
	words = 0;
	j = 0;
	while (s[i] && is_separator(s[i], separators) != '\0')
		i++;
	while (s[i++])
	{
		if (is_separator(s[i], separators) != '\0')
		{
			words++;
			j++;
			while (s[i] && is_separator(s[i], separators) != '\0')
				i++;
			continue ;
		}
	}
	if (is_separator(s[i - 1], separators) == '\0')
		words++;
	return (words);
}

static void	ft_getword(char **tab, unsigned int *strlen, char *separators)
{
	unsigned int	i;

	*tab += *strlen;
	*strlen = 0;
	i = 0;
	while (**tab && is_separator(**tab, separators) != '\0')
		(*tab)++;
	while ((*tab)[i])
	{
		if (is_separator((*tab)[i], separators) != '\0')
			return ;
		(*strlen)++;
		i++;
	}
}

char	**ft_split(char const *s, char *separators)
{
	unsigned int	wordscount;
	char			**tab;
	char			*str;
	unsigned int	strlen;
	unsigned int	i;

	if (!s)
		return (NULL);
	wordscount = ft_countwords(s, separators);
	tab = malloc(sizeof(char *) * (wordscount + 1));
	if (!(tab))
		return (NULL);
	str = (char *)s;
	strlen = 0;
	i = -1;
	while (++i < wordscount)
	{
		ft_getword(&str, &strlen, separators);
		tab[i] = malloc(sizeof(char) * (strlen + 1));
		if (!(tab[i]))
			return (ft_free_words(tab));
		ft_strlcpy(tab[i], str, strlen + 1);
	}
	tab[i] = NULL;
	return (tab);
}

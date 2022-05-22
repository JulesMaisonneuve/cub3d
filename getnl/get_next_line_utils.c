/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumaison <jumaison@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 13:58:22 by jumaison          #+#    #+#             */
/*   Updated: 2021/04/04 14:30:59 by jumaison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	*ft_memalloc(size_t size)
{
	void	*mem;
	size_t	i;
	char	*ptr2;

	mem = malloc(size);
	if (!(mem))
		return (NULL);
	ptr2 = (char *)mem;
	i = 0;
	while (i < size)
	{
		ptr2[i] = '\0';
		i++;
	}
	return (mem);
}

char	*ft_strnew(size_t size)
{
	char	*new;

	if (size == (size_t)(-1))
		return (0);
	new = ft_memalloc(size + 1);
	return (new);
}

char	*ft_strdup(const char *s1)
{
	char	*str;
	int		i;

	i = 0;
	str = malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (str == NULL)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

void	*ft_memcpy(void *dest, const void *src, size_t num)
{
	size_t	i;
	char	*ptrdest;
	char	*ptrsrc;

	if (dest == NULL && src == NULL)
		return (0);
	ptrdest = (char *)dest;
	ptrsrc = (char *)src;
	i = 0;
	while (i < num)
	{
		ptrdest[i] = ptrsrc[i];
		i++;
	}
	return (ptrdest);
}

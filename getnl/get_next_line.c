/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumaison <jumaison@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 18:10:58 by jumaison          #+#    #+#             */
/*   Updated: 2021/04/04 14:51:20 by jumaison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *str, int c)
{
	char	ch;

	ch = c;
	while (*str)
	{
		if (*str == ch)
			return ((char *)str);
		str++;
	}
	if (c == '\0')
		return ((char *)str);
	return (0);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1len;
	size_t	s2len;
	char	*str;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	str = malloc(s1len + s2len + 1);
	if (str == NULL)
		return (NULL);
	ft_memcpy(str, s1, s1len);
	ft_memcpy(str + s1len, s2, s2len + 1);
	return (str);
}

int	append_buff_line(char **actual_line, char *buffer, char **remains)
{
	char	*chr_result;
	char	*to_free;

	chr_result = ft_strchr(buffer, '\n');
	if (!(chr_result))
	{
		to_free = *actual_line;
		*actual_line = ft_strjoin(*actual_line, buffer);
		free(to_free);
		return (0);
	}
	else
	{
		*remains = ft_strdup(chr_result + 1);
		*chr_result = '\0';
		to_free = *actual_line;
		*actual_line = ft_strjoin(*actual_line, buffer);
		free(to_free);
		return (1);
	}
}

char	*treat_buffer_remains(char **buffer_remains, char **line)
{
	char	*chr_result;
	char	*to_free;
	char	*actual_line;

	if (*buffer_remains)
	{
		chr_result = ft_strchr(*buffer_remains, '\n');
		if (chr_result)
		{
			to_free = *buffer_remains;
			*chr_result = '\0';
			*line = ft_strdup(*buffer_remains);
			*buffer_remains = ft_strdup(chr_result + 1);
			free(to_free);
			return (NULL);
		}
		actual_line = ft_strdup(*buffer_remains);
		free(*buffer_remains);
		*buffer_remains = NULL;
		return (actual_line);
	}
	else
	{
		return (ft_strnew(0));
	}
}

int	get_next_line(int fd, char **line)
{
	ssize_t		bytes_read;
	char		buffer[BUFFER_SIZE + 1];
	char		*actual_line;
	static char	*buffer_remains = NULL;

	bytes_read = 0;
	if (fd < 0 || !line || BUFFER_SIZE < 1)
		return (-1);
	actual_line = treat_buffer_remains(&buffer_remains, line);
	if (actual_line == NULL)
		return (1);
	while (read(fd, buffer, BUFFER_SIZE) == 1)
	{
		bytes_read = 1;
		buffer[bytes_read] = '\0';
		if (append_buff_line(&actual_line, buffer, &buffer_remains))
			break ;
	}
	if (bytes_read < 0)
	{
		free(actual_line);
		return (-1);
	}
	*line = actual_line;
	return (bytes_read != 0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchrr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumaison <jumaison@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 20:27:09 by jumaison          #+#    #+#             */
/*   Updated: 2022/06/10 20:27:09 by jumaison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

int	ft_strchrr(const char *str, int c)
{
	char	ch;

	ch = c;
	while (*str == ch && *str)
		str++;
	if (*str != ch && *str != '\0')
		return (0);
	return (1);
}

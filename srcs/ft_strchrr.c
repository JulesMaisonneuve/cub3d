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

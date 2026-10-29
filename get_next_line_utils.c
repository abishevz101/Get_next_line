#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	d;

	i = 0;
	d = (unsigned char)c;
	while (s[i] != '\0')
	{
		if (s[i] == d)
			
		i++;
	}
}
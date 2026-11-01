#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	size_t			i;
	unsigned char	d;
	unsigned char	*x;

	i = 0;
	d = (unsigned char)c;
	x = (unsigned char *)s;
	if (x == NULL)
		return (NULL);
	while (x[i] != '\0')
	{
		if (x[i] == d)
			return ((char *)&x[i]);
		i++;
	}
	return (NULL);
}

void	ft_copy(char *dst, char *src, size_t n)
{
	size_t	i;
	size_t	len1;

	i = 0;
	len1 = n;
	while (i < len1)
	{
		dst[i] = src[i];
		i++;
	}
}

char	*ft_strjoin(char *oldstash, char *s2)
{
	char	*newstash;
	size_t	len1;
	size_t	len2;

	len1 = ft_strlen(oldstash);
	len2 = ft_strlen(s2);
	newstash = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!newstash)
	{
		free(oldstash);
		return (NULL);
	}
	ft_copy(newstash, oldstash, len1);
	ft_copy(newstash + len1, s2, len2);
	newstash[len1 + len2] = '\0';
	free (oldstash);
	return (newstash);
}

char	*ft_substr(char *s, size_t start, size_t len)
{
	char	*ptr;

	ptr = malloc(sizeof(char) * (len +1));
	if (!ptr)
		return (NULL);
	ft_copy(ptr, &s[start], len);
	ptr[len] = '\0';
	return (ptr);
}

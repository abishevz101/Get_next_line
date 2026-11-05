#include "get_next_line.h"

char	*ft_read_to_stash(int fd, char *stash)
{
	char	*buf;
	ssize_t	bytes;

	bytes = 1;
	buf = malloc(sizeof(char) * (BUFFER_SIZE +1));
	if (!buf)
	{
		free(stash);
		return (NULL);
	}
	while (ft_strchr(stash, '\n') == NULL && bytes > 0)
	{
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(buf);
			free(stash);
			return (NULL);
		}
		buf[bytes] = '\0';
		stash = ft_strjoin(stash, buf);
	}
	free(buf);
	return (stash);
}

char	*ft_extract_line(char *stash)
{
	char	*a;
	size_t	b;

	if (stash == NULL || stash[0] == '\0')
		return (NULL);
	a = ft_strchr(stash, '\n');
	if (a != NULL)
		b = a - stash + 1;
	else
		b = ft_strlen(stash);
	return (ft_substr(stash, 0, b));
}

char	*ft_clean_stash(char *stash)
{
	char	*a;
	size_t	start;
	char	*k;

	if (stash == NULL)
		return (NULL);
	a = ft_strchr(stash, '\n');
	if (a == NULL)
	{
		free (stash);
		return (NULL);
	}
	start = a - stash + 1;
	k = ft_substr(stash, start, ft_strlen(stash) - start);
	free (stash);
	return (k);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = ft_read_to_stash(fd, stash);
	if (stash == NULL)
		return (NULL);
	line = ft_extract_line(stash);
	stash = ft_clean_stash(stash);
	return (line);
}

#include "get_next_line.h"

char	*read_to_stash(int fd, char *stash)//читет из fd кусками и дописывает их в stash
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


char	*get_next_line(int fd)
{
	static char	*stash;

	return (NULL);
}

//fd — откуда читать (параметр твоей функции);
// buf — куда положить (твоя корзинка);
// count — сколько максимум прочитать (BUFFER_SIZE).
//read возвращает не «-1 либо +1», а -1, 0 или количество прочитанных байт (например, 42).


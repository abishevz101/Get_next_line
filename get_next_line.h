#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <stdlib.h>

char	*get_next_line(int fd);
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
void	ft_copy(char *dst, char *src, size_t n);
char	*ft_strjoin(char *oldstash, char *s2);
char	*ft_substr(char *s, size_t start, size_t len);

#endif
*This project has been created as part of the 42 curriculum by zabishev.*

# Get Next Line

## Description

`get_next_line` is a C function that returns one line at a time from a file descriptor:

```c
char *get_next_line(int fd);
```

Repeated calls read the file (or standard input) line by line. The returned line includes the terminating `\n`, except when the end of the file is reached and the file does not end with a newline. When there is nothing left to read, or an error occurs, the function returns `NULL`.

The goal of the project is to learn about `static` variables, dynamic memory management, and the `read` system call. Allowed external functions: `read`, `malloc`, `free`.

### Files

| File | Content |
|---|---|
| `get_next_line.c` | `get_next_line` and its main helpers (`ft_read_to_stash`, `ft_extract_line`, `ft_clean_stash`) |
| `get_next_line_utils.c` | String helpers (`ft_strlen`, `ft_strchr`, `ft_copy`, `ft_strjoin`, `ft_substr`) |
| `get_next_line.h` | Prototypes, includes, and the default `BUFFER_SIZE` |

## Instructions

### Compilation

The `BUFFER_SIZE` macro defines how many bytes are requested per `read()` call. It can be set at compile time:

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c
```

If `-D BUFFER_SIZE` is omitted, the header defines a default value of `42`.

### Usage

```c
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int main(void)
{
	int		fd;
	char	*line;

	fd = open("file.txt", O_RDONLY);
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
```

Reading from standard input also works: call `get_next_line(0)`.

The caller must `free` every returned line.

### Testing tips

Try several buffer sizes (`1`, `42`, `9999`, `10000000`), empty files, files without a trailing newline, files with only newlines, very long lines, standard input, and invalid file descriptors.

## Algorithm

The function uses a single `static char *stash` that persists between calls and holds data that was read from the file descriptor but not yet returned.

Each call to `get_next_line(fd)` does three steps:

1. **Read into the stash** (`ft_read_to_stash`): allocate a buffer of `BUFFER_SIZE + 1` bytes and call `read()` repeatedly, appending each chunk to the stash with `ft_strjoin`. The loop stops as soon as the stash contains a `\n`, or `read()` returns `0` (end of file). If `read()` returns `-1`, everything is freed and `NULL` is returned.
2. **Extract the line** (`ft_extract_line`): copy the stash from its start up to and including the first `\n` (or up to the end if there is no newline) into a newly allocated string. An empty or `NULL` stash yields `NULL`, which signals the end of the file.
3. **Clean the stash** (`ft_clean_stash`): keep only what follows the returned line (the leftover that was read past the `\n`). If there is no newline left, the stash is freed and set to `NULL`.

### Why this approach

- **A static stash** is the natural way to keep the leftover bytes between calls without using global variables (which are forbidden).
- **Stopping the read loop at the first `\n`** means we read as little as possible and never load the whole file in memory, as the subject requires.
- **Reading in `BUFFER_SIZE` chunks** works for any size: with `1` it is simply slow (one syscall per byte), and with a very large value the leftover simply stays in the stash for the next calls. The buffer is allocated on the heap, so a huge `BUFFER_SIZE` does not overflow the stack.
- **Joining into a fresh string** at each step keeps the code simple and the ownership of memory clear: every intermediate allocation is freed immediately, so there are no leaks.

### Limitations

- The stash is a single `static` variable, so only one file descriptor can be tracked at a time. Interleaving calls on different descriptors would mix their data. (Handling multiple descriptors is the bonus part, which is not implemented here.)
- Behavior is undefined if the file is modified between calls before EOF is reached, or when reading binary files, as allowed by the subject.

## Resources

- `man 2 read`, `man 3 malloc`, `man 3 free`
- [Static variables in C (GeeksforGeeks)](https://www.geeksforgeeks.org/static-variables-in-c/)
- 42 Get Next Line subject

### Use of AI

AI (Claude) was used only to help with an explanation what static variable is and helped to understand some functions or how to implement static variable and work with it in the function. The code itself (`get_next_line.c`, `get_next_line_utils.c`, `get_next_line.h`) was written by the author.

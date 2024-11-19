#include "get_next_line.h"
#include <stdio.h>

int main(int argc, char **argv)
{
    int fd = open(argv[1], O_RDONLY);
    char *line;

    if (argc < 2)
	    return (0);
    if (fd < 0)
    {
        write(2, "Error opening file", 18);
        return (1);
    }

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }

    close(fd);
    return (0);
}

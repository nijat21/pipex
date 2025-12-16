#include "pipex.h"

void *safe_malloc(size_t bytes)
{
    void *mem;

    mem = malloc(bytes);
    if (!mem)
    {
        error_exit("Malloc", false, true);
        return (NULL);
    }
    return (mem);
}

void safe_close(int fd, t_pipex *px)
{
    if (close(fd) != 0)
    {
        free(px);
        error_exit("Close", true, true);
    }
}

void safe_waitpid(int pid, t_pipex *px)
{
    if (waitpid(pid, NULL, 0))
        ;
}

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

int safe_waitpid(pid_t pid)
{
    int status;

    if (waitpid(pid, &status, 0) == -1)
    {
        perror("Waitpid");
        return -1;
    }
    if (WIFEXITED(status))
        return (WEXITSTATUS(status));
    else if (WIFSIGNALED(status))
        return (128 + WTERMSIG(status));
    return -1;
}

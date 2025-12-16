#include "pipex.h"

void *parse_input(char **av, t_pipex *px)
{
    px->fd_in = open(av[1], O_RDONLY);
    if (px->fd_in == -1)
    {
        free(px);
        error_exit("File", true, true);
    }
    px->cmd1 = ft_split(av[2], ' ');
    px->cmd2 = ft_split(av[3], ' ');
    px->fd_out = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (px->fd_in == -1)
    {
        free(px);
        close(px->fd_in);
        error_exit("File", true, true);
    }
    if (pipe(px->pipefd) == -1)
    {
        free(px);
        close(px->fd_in);
        close(px->fd_out);
        error_exit("Pipe", true, true);
    }
    return px;
}
#include "pipex.h"

int shell_exec_error(char *cmd)
{
    perror(cmd);
    if (errno == ENOENT)
        exit(CMD_NOT_FOUND);
    else if (errno == EACCES || errno == EISDIR || errno == ENOTDIR)
        exit(CMD_NOT_EXEC);
    exit(EXIT_FAILURE);
}

void error_exit(char *msg, bool leave, bool use_perror)
{
    if (use_perror)
        perror(msg);
    else
        ft_putendl_fd(msg, STDERR_FILENO);
    if (leave)
        exit(EXIT_FAILURE);
}
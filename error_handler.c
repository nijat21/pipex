#include "pipex.h"

void error_exit(char *msg, bool stop, bool use_perror)
{
    if (use_perror)
        perror(msg);
    else
        ft_printf("%s\n", msg);
    if (stop)
        exit(EXIT_FAILURE);
}
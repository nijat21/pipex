#include "pipex.h"

void error_exit(char *msg, bool stop)
{
    ft_printf(msg);
    if (stop)
        exit(EXIT_FAILURE);
}
#include "pipex.h"

void error_exit(char *msg, bool exit)
{
    ft_printf(msg);
    exit(EXIT_FAILURE);
}
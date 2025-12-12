#ifndef PIPEX_H
#define PIPEX_H

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "ft_printf/ft_printf.h"

typedef struct s_pipex {
    int fd_in;
    int fd_out;
    int pipefd[2];
    char **cmd1;
    char **cmd2;
} t_pipex;


#endif

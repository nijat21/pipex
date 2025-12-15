#ifndef PIPEX_H
#define PIPEX_H

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "Libft/libft.h"

typedef struct s_pipex
{
    int pid_ch1;
    int pid_ch2;
    int fd_in;
    int fd_out;
    int pipefd[2];
    char **cmd1;
    char **cmd2;
} t_pipex;

void error_exit(char *msg, bool stop, bool use_perror);
char *resolve_path(char **env, char *cmd);

#endif

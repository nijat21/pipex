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
#include "errno.h"

// execve errors
#define CMD_NOT_FOUND 127
#define CMD_NOT_EXEC 126

typedef struct s_pipex
{
    pid_t pid_ch;
    int fd_in;
    int fd_out;
    int pipefd[2];
    char **cmd;
} t_pipex;

// typedef struct s_pipex
// {
//     pid_t *pid_childs;
//     int fd_in;
//     int fd_out;
//     int **pipefd;
//     char ***cmds;
// } t_pipex;

// parser
void *parse_input(char **av, t_pipex *px);
//
char *resolve_path(char **env, char *cmd);
// error handling
int shell_exec_error(char *msg);
void error_exit(char *msg, bool stop_program, bool use_perror);
// safe functions
void *safe_malloc(size_t bytes);
int safe_waitpid(pid_t pid);

// utils
void free_str_arr(char **arr);
void free_int_arr(int **arr, int len);
void free_px(t_pipex *px, int ncmd);

#endif

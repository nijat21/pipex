#include "pipex.h"

static void *parse_input(char **av, t_pipex *px)
{
	px->fd_in = open(av[1], O_RDONLY);
	if (px->fd_in == -1)
	{
		free(px);
		error_exit("Error: Couldn't open the file\n", true);
	}
	px->cmd1 = ft_split(av[2], ' ');
	px->cmd2 = ft_split(av[3], ' ');
	px->fd_out = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (px->fd_in == -1)
	{
		free(px);
		close(px->fd_in);
		error_exit("Error: Couldn't open the file\n", true);
	}
	if (pipe(px->pipefd) == -1)
	{
		free(px);
		close(px->fd_in);
		close(px->fd_out);
		error_exit("Error: Pipe error\n", true);
	}
	return px;
}

void first_child(t_pipex *px, char **env)
{
	// < files ls
	dup2(px->fd_in, STDIN_FILENO);
	dup2(px->pipefd[1], STDOUT_FILENO);
	close(px->fd_in);
	close(px->pipefd[0]);
	close(px->pipefd[1]);
	execve("/usr/bin/ls", px->cmd1, env);
	perror("execve");
	exit(EXIT_FAILURE);
}

void second_child(t_pipex *px, char **env)
{
	// | echo > output.txt
	dup2(px->pipefd[0], STDIN_FILENO);
	dup2(px->fd_out, STDOUT_FILENO);
	close(px->fd_out);
	close(px->pipefd[0]);
	close(px->pipefd[1]);
	execve("/usr/bin/cat", px->cmd2, env);
	perror("execve");
	exit(EXIT_FAILURE);
}

void run_processes(char **av, char **env)
{
	t_pipex *px;

	px = malloc(sizeof(t_pipex));
	if (!px)
		error_exit("Error: Malloc failed\n", true);
	parse_input(av, px);
	if (pipe(px->pipefd) != 0)
	{
		perror("pipe");
		free(px);
		exit(EXIT_FAILURE);
	}
	px->pid_ch1 = fork();
	if (px->pid_ch1 < 0) // error
	{
		free(px);
		exit(EXIT_FAILURE);
	}
	if (px->pid_ch1 == 0) // in parent
		first_child(px, env);

	px->pid_ch2 = fork();
	if (px->pid_ch2 < 0) // error
	{
		free(px);
		exit(EXIT_FAILURE);
	}
	if (px->pid_ch2 == 0) // in parent
		second_child(px, env);
	close(px->pipefd[0]);
	close(px->pipefd[1]);
	waitpid(px->pid_ch1, NULL, 0);
	waitpid(px->pid_ch2, NULL, 0);
}

int main(int ac, char **av, char **env)
{
	/*
	 * input -> ./pipex file1 cmd1 cmd2 file2
	 * behavior -> < file1 cmd1 | cmd2 > file2

	 WORKFLOW:
	 1. Open file1
	 2. Give file1 STDIN to cmd1
	 3. Close file1
	 4. Pass the result of step 2 as STDIN to cmd2
	 5. Close file2

	 */
	if (ac != 5)
		return 0;

	run_processes(av, env);

	return 0;
}

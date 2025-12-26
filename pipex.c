#include "pipex.h"

void first_child(t_pipex *px, char **env)
{
	char *path;
	// < files ls
	dup2(px->fd_in, STDIN_FILENO);
	dup2(px->pipefd[1], STDOUT_FILENO);
	close(px->fd_in);
	close(px->pipefd[0]);
	close(px->pipefd[1]);
	path = resolve_path(env, px->cmd[0]);
	if (!path)
		error_exit(ft_strjoin3("Error: Command not found: ", px->cmd[0], "\n"), true, false);
	execve(path, px->cmd, env);
	shell_exec_error(px->cmd[0]);
}

void mid_child(t_pipex *px, char **env)
{
	char *path;
	// | cmd2 -> | cmd3 -> ...
	dup2(px->pipefd[0], STDIN_FILENO);
	dup2(px->pipefd[1], STDOUT_FILENO);
	close(px->pipefd[0]);
	close(px->pipefd[1]);
	path = resolve_path(env, px->cmd[0]);
	if (!path)
		error_exit(ft_strjoin3("Error: Command not found:", px->cmd[0], "\n"), true, false);
	execve(path, px->cmd, env);
	shell_exec_error(px->cmd[0]);
}

void second_child(t_pipex *px, char **env)
{
	char *path;
	// | echo > output.txt
	dup2(px->pipefd[0], STDIN_FILENO);
	dup2(px->fd_out, STDOUT_FILENO);
	close(px->fd_out);
	close(px->pipefd[0]);
	close(px->pipefd[1]);
	path = resolve_path(env, px->cmd[0]);
	if (!path)
		error_exit(ft_strjoin3("Error: Command not found:", px->cmd[0], "\n"), true, false);
	execve(path, px->cmd, env);
	shell_exec_error(px->cmd[0]);
}

void run_processes(int ac, char **av, char **env)
{
	t_pipex *px;
	int status_ch2;
	int i;
	int ncomd;

	ncomd = ac - 3;

	px = (t_pipex *)safe_malloc(sizeof(t_pipex));
	if (!px)
		exit(EXIT_FAILURE);

	// parse_input(av, px); ->
	px->fd_in = open(av[1], O_RDONLY);
	if (px->fd_in == -1)
	{
		free(px);
		error_exit("File", true, true);
	}
	px->fd_out = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (px->fd_in == -1)
	{
		free(px);
		close(px->fd_in);
		error_exit("File", true, true);
	}
	px->cmd = ft_split(av[2], ' ');

	// for each command
	i = -1;
	while (++i < ncomd) // last av is output.txt
	{
		// pipe once
		if (i != ncomd - 1)
			if (pipe(px->pipefd) == -1)
			{
				free(px);
				close(px->fd_in);
				close(px->fd_out);
				error_exit("Pipe", true, true);
			}
		px->pid_ch = fork();
		if (px->pid_ch < 0)
		{
			free(px);
			exit(EXIT_FAILURE);
		}
		if (px->pid_ch == 0)
		{
			if (i == 0)
				first_child(px, env);
			else if (i == ncomd - 1)
				second_child(px, env);
			else
				mid_child(px, env);
			if (close(px->pipefd[0]) != 0 || close(px->pipefd[1]) != 0)
			{
				free(px);
				error_exit("Close", true, true);
			}
			safe_waitpid(px->pid_ch);
		}
	}

	free(px);
	exit(status_ch2);
}

int main(int ac, char **av, char **env)
{
	/*
	mandatory:
	 * input -> ./pipex file1 cmd1 cmd2 file2
	bonus:
	 * input -> ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2
	 */
	if (ac != 5)
		return 0;

	run_processes(ac, av, env);

	return 0;
}

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
	path = resolve_path(env, px->cmd1[0]);
	if (!path)
		error_exit("Error: Command not found\n", true, false);
	execve(path, px->cmd1, env);
	shell_exec_error(px->cmd1[0]);
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
	path = resolve_path(env, px->cmd2[0]);
	if (!path)
		error_exit("Error: Command not found\n", true, false);
	execve(path, px->cmd2, env);
	shell_exec_error(px->cmd2[0]);
}

void run_processes(char **av, char **env)
{
	t_pipex *px;

	px = (t_pipex *)safe_malloc(sizeof(t_pipex));
	if (!px)
		exit(EXIT_FAILURE);
	parse_input(av, px);
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
	safe_close(px->pipefd[0], px);
	safe_close(px->pipefd[1], px);
	waitpid(px->pid_ch1, NULL, 0); // WIP
	waitpid(px->pid_ch2, NULL, 0);
}

int main(int ac, char **av, char **env)
{
	/*
	 * input -> ./pipex file1 cmd1 cmd2 file2
	 * behavior -> < file1 cmd1 | cmd2 > file2
		Resolve commands via PATH (no hardcoded paths)
		Handle:
			invalid commands
			permission errors
			missing files
		Close FDs correctly in all branches
		Understand who exits and who returns
	 */
	if (ac != 5)
		return 0;

	run_processes(av, env);

	return 0;
}

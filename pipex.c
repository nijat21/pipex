#include "pipex.h"

void first_child(t_pipex *px, char **env)
{
	printf("first\n");
	char *path;
	// < files ls
	if (dup2(px->fd_in, STDIN_FILENO) < 0 || dup2(px->pipefd[1], STDOUT_FILENO) < 0)
	{
		close(px->fd_out);
		close(px->pipefd[0]);
		close(px->pipefd[1]);
		perror("Dup2");
		exit(EXIT_FAILURE);
	}
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
	printf("mid\n");
	char *path;
	// | cmd2 -> | cmd3 -> ...
	if (dup2(px->pipefd[0], STDIN_FILENO) < 0 || dup2(px->pipefd[1], STDOUT_FILENO) < 0)
	{
		close(px->pipefd[0]);
		close(px->pipefd[1]);
		perror("Dup2");
		exit(EXIT_FAILURE);
	}
	close(px->fd_in);
	close(px->fd_out);
	close(px->pipefd[0]);
	close(px->pipefd[1]);
	path = resolve_path(env, px->cmd[0]);
	if (!path)
		error_exit(ft_strjoin3("Error: Command not found:", px->cmd[0], "\n"), true, false);
	execve(path, px->cmd, env);
	shell_exec_error(px->cmd[0]);
}

void last_child(t_pipex *px, char **env)
{
	printf("last\n");
	char *path;
	// | echo > output.txt
	if (dup2(px->pipefd[0], STDIN_FILENO) < 0 || dup2(px->fd_out, STDOUT_FILENO) < 0)
	{
		close(px->fd_out);
		close(px->pipefd[0]);
		close(px->pipefd[1]);
		perror("Dup2");
		exit(EXIT_FAILURE);
	}
	close(px->fd_out);
	close(px->pipefd[0]);
	close(px->pipefd[1]);
	path = resolve_path(env, px->cmd[0]);
	printf("path -> %s\n", path);
	if (!path)
		error_exit(ft_strjoin3("Error: Command not found:", px->cmd[0], "\n"), true, false);
	execve(path, px->cmd, env);
	shell_exec_error(px->cmd[0]);
	printf("execed\n");
}

void run_processes(int ac, char **av, char **env)
{
	t_pipex *px;
	int status_ch;
	int i;
	int ncmds;

	ncmds = ac - 3;
	px = (t_pipex *)safe_malloc(sizeof(t_pipex));
	if (!px)
		exit(EXIT_FAILURE);

	// parse_input(av, px); ->
	px->fd_in = open(av[1], O_RDONLY);
	if (px->fd_in == -1)
	{
		free_px(px);
		error_exit("File", true, true);
	}
	px->fd_out = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (px->fd_out == -1)
	{
		free_px(px);
		close(px->fd_in);
		error_exit("File", true, true);
	}
	px->pid_ch = safe_malloc(sizeof(int) * ncmds);
	if (!px->pid_ch)
	{
		close(px->fd_in);
		close(px->fd_out);
		free_px(px);
		error_exit("Malloc", true, true);
	}

	// for each command
	i = -1;
	while (++i < ncmds) // last av is output.txt
	{
		// pipe once
		if (i < ncmds - 1)
			if (pipe(px->pipefd) < 0)
			{
				close(px->fd_in);
				close(px->fd_out);
				free_px(px);
				error_exit("Pipe", true, true);
			}
		px->pid_ch[i] = fork();
		if (px->pid_ch[i] < 0)
		{
			free_px(px);
			error_exit("Fork", true, true);
		}

		px->cmd = ft_split(av[i + 2], ' ');
		if (!px->cmd)
		{
			free_px(px);
			error_exit("Cmd split", true, true);
		}
		if (px->pid_ch[i] == 0)
		{
			if (i == 0)
				first_child(px, env);
			else if (i == ncmds - 1)
				last_child(px, env);
			else
				mid_child(px, env);
		}
		else
		{
			// close parent fd-s right after fork
			close(px->fd_in);
			if (i < ncmds - 1)
			{
				close(px->pipefd[1]);
				px->fd_in = close(px->pipefd[0]);
			}
			if (i == ncmds - 1)
				close(px->fd_out);

			printf("back in parent\n");
		}
	}

	i = -1;
	while (++i < ncmds)
		status_ch = safe_waitpid(px->pid_ch[i]);
	free_px(px);
	exit(status_ch);
}

int main(int ac, char **av, char **env)
{
	/*
	mandatory:
	 * input -> ./pipex file1 cmd1 cmd2 file2
	bonus:
	 * input -> ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2
	 */
	if (ac < 5)
		return 0;

	run_processes(ac, av, env);

	return 0;
}

#include "pipex.h"

static void * parse_input(int ac, char **av, t_pipex *props){
	
	*fd_infile = open(av[1], O_RDONLY);
	if(*fd_infile == -1) error_exit("Error: Couldn't open the file\n");
	*fd_outfile = open(av[4], O_WRONLY | O_CREATE | O_TRUNC, 0644);
	if(*fd_infile == -1) {
		close(fd_infile);
		ft_printf("Error: Couldn't open the file\n");
		return NULL;
	}
	return props;
}


int main()
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

	

	// if(ac != 5) return 0;
	parse_input(int ac, char **av, &fd_infile, &fd_outfile);



	ft_printf("something\n");
	return 0;
}	

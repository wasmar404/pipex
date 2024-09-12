/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 14:09:10 by wasmar            #+#    #+#             */
/*   Updated: 2024/09/12 09:28:23 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
/*
    - The child function will run before the parent.
    - we open the file; if fd_child is -1, an error exists.
    - Redirect the standard output (stdout) of the child process to the write end of the pipe (fd[1]).
    - then set the input to be from the opened file using: dup2(fd_child, 0);
    - tClose the read end of the pipe (fd[0]), as it is not needed in the child process.
    - Then, execute the command.
*/
void	child(char **argv, char **envp, int *fd)
{
	int		fd_child;

	fd_child = open(argv[1], O_RDONLY, 0777);
	if (fd_child == -1)
		error();
	dup2(fd[1], 1);
	dup2(fd_child, 0);
	close(fd[0]);
	execute_command(argv[2], envp);
}


/* 
    - This function will run after the child process. and It will also execute the second command.
    - Redirect the input from the read end of the pipe (fd[0]) instead of from stdin.
    - Redirect the output to the file instead of stdout.
    - Close the write end of the pipe (fd[1]) as it will not be needed.
    - Execute the command.
 */
void	parent(char **argv, char **envp, int *fd)
{
	int		fd_parent;

	fd_parent = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd_parent == -1)
		error();
	dup2(fd[0], 0);
	dup2(fd_parent, 1);
	close(fd[1]);
	execute_command(argv[3], envp);
}

/* 
    - First, I create a pipe and when I call the pipe function, it fills fd[0] with 3,
      which is the read end of the pipe, and fd[1] with 4, which is the write end of the pipe.
    - If pipe returns -1, it indicates an error, so I write an error message and exit.
    - If the pipe is created successfully, I create a fork and assign the ID to fork_id.
      If the fork function returns -1, it indicates an error, so I write an error message and exit.
    - If fork_id is zero, this means it is the child process, so I call the child function.
    - Then I wait to make sure that the child process is done before the parent process starts working.
    - If the number of arguments is less than 5, I write an error message.
*/
int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	int	    fork_id;

	if (argc == 5)
	{
		if (pipe(fd) == -1)
			error();
		fork_id = fork();
		if (fork_id == -1)
			error();
		if (fork_id == 0)
			child(argv, envp, fd);
        wait(&fork_id);
		parent(argv, envp, fd);
	}
	else if(argc == 3)
		input_to_output_file(argv);
	else
    	write(1,"ERROR",5);
	return (0);
}
void input_to_output_file(char **argv)
{
	int fd_infile;
	int fd_outfile;
	char *array;
	fd_infile = open(argv[1],R_OK);
	fd_outfile = open(argv[2],O_WRONLY | O_CREAT | O_TRUNC, 0644);

	array = get_next_line(fd_infile);
	
	while (array != NULL)
	{
		write(fd_outfile,array,ft_strlen(array));
		free(array);
		array = get_next_line(fd_infile);
	}
	
}

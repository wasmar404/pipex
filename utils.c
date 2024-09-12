/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 09:40:09 by wasmar            #+#    #+#             */
/*   Updated: 2024/09/12 09:35:20 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
/*
    The goal of this function is to find the "PATH=" environment variable.
    - This function takes a triple pointer (`char ***envp`). It modifies the `envp` directly, so no value is returned.
    - It loops through the `envp` array as long as it is not `NULL`.
    - When `ft_strnstr` returns a non-NULL value, it indicates that the function has found the "PATH=" in the environment variable.
*/

void find_the_word_path_in_envp(char ***envp)
{
    while (**envp != NULL) {
    if (ft_strnstr(**envp, "PATH=", 5) != NULL) 
        return;
    (*envp)++;
}
}

/*
    - This function takes two parameters: the command and the environment variables.
    - First, it calls the "find_the_word_path_in_envp(&envp);" function to locate the "PATH=" environment variable.
    - It then splits the value of "PATH=" into a 2D array based on the ":" delimiter.
    - Next, it uses `strjoin` to append the command to each path in the array. If the file is accessible, it means the command was found; if not, it frees the memory and continues to the next path.
    - If a valid path is found, it returns it. Otherwise, it returns NULL.
*/
char *find_path_of_cmd(char *command, char **envp) 
{
    char **all_path;
    char *cmd_path;
    char *temp;
    int i ;


    find_the_word_path_in_envp(&envp);
    all_path = ft_split(*envp + 5, ':'); 
    i = 0;
    while (all_path[i] != NULL) 
    {
        temp = ft_strjoin(all_path[i], "/");
        cmd_path = ft_strjoin(temp, command);
        free(temp);
        if (access(cmd_path, X_OK) == 0) 
        {
            free_array(all_path);
            return cmd_path;
        }
        free(cmd_path);
        i++;
    }
    free_array(all_path);
    return (NULL);
}

/*
    - The goal of this function is to execute the command entered by the user using execve.
    - First, split the command using ft_split with space as the delimiter.
    - Then, find the path for the command using "find_path_of_cmd" function.
    - If no path is found, free the splited array, print an error, and exit.
    - If a path is found, run the command using execve. If execve returns -1, it indicates an error, so print an error and exit.
*/

void execute_command(char *input, char **envp)
{
    char **command;
    char *path_of_cmd;
    int     i;
    i = 0;
    if(check_space(input)== 0)
        error();
    command = ft_split(input,' ');
    path_of_cmd = find_path_of_cmd(command[0],envp);
    if (!path_of_cmd)
    {
        free_array(command);
        error();
    }
    if(execve(path_of_cmd,command,envp) == -1)
    {
                free_array(command);
        error();
    }
}
/*
    - The goal of this function is to check that the input is not null and does not contain only spaces.
    - If it contains only spaces or is null, I return 0; otherwise, if it contains any characters, I return 1.
*/

int check_space(char *input)
{
    int i = 0 ;
    int j = 0;
    while(input[i])
    {
        
        if(input[i] != ' ')
            j++;
        i++;
    }   
    if(j == 0)
    {
        return (0);
    } 
    return 1;
}

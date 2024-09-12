/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 09:40:14 by wasmar            #+#    #+#             */
/*   Updated: 2024/09/12 09:28:49 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  PIPEX_H
# define PIPEX_H
# include <unistd.h>
# include <stdlib.h>  
#include <fcntl.h>   
 #include <sys/wait.h> 
char **ft_split(const char *s, char c);
char **ft_split(const char *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
void free_array(char **array);
size_t	ft_strlen(const char *s);
char	*ft_strnstr(char const *haystack, char const *needle, size_t n);
char	*find_path(char *cmd, char **envp);
char	*get_next_line(int fd);
void find_the_word_path_in_envp(char ***envp);
char *find_path_of_cmd(char *command, char **envp);
int check_space(char *input);
void input_to_output_file(char **argv);
void execute_command(char *input, char **envp);
void error(void);
#	endif


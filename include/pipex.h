/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42.madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:13:47 by jdorazio          #+#    #+#             */
/*   Updated: 2025/01/07 17:13:47 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>

# include "../libft/libft.h"

// Main file
int		main(int ac, char **av, char **env);
void	child(char **av, int *p_fd, char **env);
void	parent(char **av, int *p_fd, char **env);
int		open_file(char *av, int stdinput);
void	exec_cmd(char *cmd_str, char **env);

// Utils File
void	exit_handler(int n_exit);
char	*get_command_path(char *cmd, char **env);
char	*ft_getenv(const char *name, char **env);
char	*ft_strjoin_three(const char *s1, const char *s2, const char *s3);
void	ft_free_array(char **array);

#endif

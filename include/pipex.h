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

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#include "../libft/include/libft.h"

int	open_file(char *file, int in_out);
void	exec(char *cmd_str, char **env);
void	child(char **av, int *c_fd, char **env);
void	parent(char **av, int *p_fd, char **env);
void	exit_handler (int n_exit);
char	*ft_getenv(char *name, char **env);
char	*get_command_path(char*cmd, char **env);

int	main(int ac, char **av, char **envp);

#endif

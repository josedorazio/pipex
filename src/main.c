/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42.madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:17:23 by jdorazio          #+#    #+#             */
/*   Updated: 2025/01/07 17:17:23 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/pipex.h"

int	open_file(char *file, int in_out)
{
	int	buf;

	if (in_out == 0)
		buf = open(file, O_RDONLY);
	if (in_out == 1)
		buf = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (buf == -1)
	{
		printf("Error opening file\n");
		exit(0);
	}
	return(buf);
}

void	exec(char *cmd_str, char **env)
{
	char	**cmd;
	char	*cmd_path;

	cmd = ft_split(cmd_str, ' ');
	if (!cmd || cmd[0])
	{
		printf("Command Error 1");
		exit(EXIT_FAILURE);
	}
	cmd_path = get_command_path(cmd[0], env);
	if (!cmd_path)
	{
		printf("Command not found 2\n");
		exit_handler(0);
	}
	if (execve(cmd_path, cmd, env) == -1)
	{
		printf("Execution error 3");
		free(cmd_path);
		exit(EXIT_FAILURE);
	}

}

void	child(char **av, int *c_fd, char **env)
{
	int fd;

	fd = open_file(av[1], 0);
	dup2(fd, 0);
	dup2(c_fd[1], 1);
	close(fd);
	close(c_fd[0]);
	exec(av[2], env);
}

void	parent(char **av, int *p_fd, char **env)
{
	int	fd;

	fd = open_file(av[4], 1);
	dup2(fd, 1);
	dup2(p_fd[0], 0);
	close(fd);
	close(p_fd[1]);
	exec(av[3], env);
}

int	main(int ac, char **av, char **env)
{
	int		p_fd[2];
	pid_t	pd;

	if (ac != 5)
		exit_handler (1);
	if (pipe(p_fd) == -1)
		exit(-1);
	pd = fork();
	if (pd == -1)
		exit (-1);
	if (pd == 0)
		child(av, p_fd, env);
	else
	{
		wait(NULL);
		parent(av, p_fd, env);
	}
	return (0);
}

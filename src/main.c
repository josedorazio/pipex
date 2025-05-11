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

#include "pipex.h"

void	exec_cmd(char *cmd_str, char **env)
{
	char	**cmd_args;
	char	*cmd_path;

	cmd_args = ft_split(cmd_str, ' ');
	if (!cmd_args || !cmd_args[0])
	{
		ft_free_array(cmd_args);
		exit_handler(5);
	}
	cmd_path = get_command_path(cmd_args[0], env);
	if (!cmd_path)
	{
		ft_free_array(cmd_args);
		exit_handler(7);
	}
	if (execve(cmd_path, cmd_args, env) == -1)
	{
		perror("Command execution error");
		free(cmd_path);
		ft_free_array(cmd_args);
		exit(0);
	}
	free(cmd_path);
	ft_free_array(cmd_args);
}

void	child(char **av, int *p_fd, char **env)
{
	int	fd;

	close(p_fd[0]);
	fd = open_file(av[1], 0);
	if (fd == -1)
	{
		close(p_fd[1]);
		exit_handler(5);
	}
	dup2(fd, 0);
	dup2(p_fd[1], 1);
	close(fd);
	close(p_fd[1]);
	exec_cmd(av[2], env);
}

void	parent(char **av, int *p_fd, char **env)
{
	int	fd;

	close(p_fd[1]);
	fd = open_file(av[4], 1);
	if (fd == -1)
	{
		close(p_fd[0]);
		exit_handler(5);
	}
	dup2(p_fd[0], STDIN_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	close(p_fd[0]);
	exec_cmd(av[3], env);
}

void	exec_process(char **av, int *p_fd, char **env, int is_child)
{
	if (is_child == 0)
		child (av, p_fd, env);
	else
		parent(av, p_fd, env);
}

int	main(int ac, char **av, char **env)
{
	int		p_fd[2];
	pid_t	pid;

	if (ac != 5)
		exit_handler (1);
	if (!env)
		exit_handler(2);
	if (pipe(p_fd) == -1)
		exit_handler(3);
	pid = fork();
	if (pid == -1)
		exit_handler(4);
	exec_process(av, p_fd, env, pid);
	return (0);
}

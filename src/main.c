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

int	open_file(char *file, int stdin_out)
{
	int	fd;

	if (stdin_out == 0)
	{
		if (access(file, F_OK) != 0)
		{
			perror("ERROR: Archivo de entrada no encontrado\n");
				return(1);
		}

		fd = open(file, O_RDONLY);
	}
	if (stdin_out == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
	{
		free(file);
		exit_handler(4);
	}
	return (fd);
}

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
		exit_handler(6);
	}
	if (execve(cmd_path, cmd_args, env) == -1)
	{
		perror("Command execution error");
		free(cmd_path);
		ft_free_array(cmd_args);
		exit(7);
	}
	free(cmd_path);
	ft_free_array(cmd_args);
}

void	child(char **av, int *p_fd, char **env)
{
	int	fd;

	fd = open_file(av[1], 0);
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		free(env);
		free(av);
		exit_handler(4);
	}
	if (dup2(p_fd[1], STDOUT_FILENO) == -1)
	{
		free(env);
		free(av);
		exit_handler(4);
	}
	close(fd);
	close(p_fd[0]);
	close(p_fd[1]);
	exec_cmd(av[2], env);
}

void	parent(char **av, int *p_fd, char **env)
{
	int	fd;

	fd = open_file(av[4], 1);
	if (dup2(p_fd[0], STDIN_FILENO) == -1)
		exit_handler(4);
	if (dup2(fd, STDOUT_FILENO) == -1)
		exit_handler(4);
	close(fd);
	close(p_fd[0]);
	close(p_fd[1]);
	exec_cmd(av[3], env);
}

int	main(int ac, char **av, char **env)
{
	int		p_fd[2];
	pid_t	pid;

	if (ac != 5)
		exit_handler (1);
	if (pipe(p_fd) == -1)
		exit_handler(2);
	pid = fork();
	if (pid == -1)
		exit_handler(3);
	if (pid == 0)
		child(av, p_fd, env);
	else
	{
		waitpid(pid, NULL, 0);
		parent(av, p_fd, env);
	}
	return (0);
}

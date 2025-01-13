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
	int	bf;

	if (stdin_out == 0)
		bf = open(file, O_RDONLY);
	if (stdin_out == 1)
		bf = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (bf == -1)
		exit_handler(4);
	return (bf);
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
		exit_handler(4);
	if (dup2(p_fd[1], STDOUT_FILENO) == -1)
		exit_handler(4);
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
	printf("1. correct amount of inputs\n");
	if (pipe(p_fd) == -1)
		exit_handler(2);
	printf("2. pipe is working correctly\n");;
	pid = fork();
	if (pid == -1)
		exit_handler(3);
	printf("3. Fork is correct\n");
	if (pid == 0)
	{
		child(av, p_fd, env);
		printf("4. Child works\n");
	}
	else
	{
		wait(NULL);
		parent(av, p_fd, env);
		printf("5. Parent works\n");
	}
	return (0);
}

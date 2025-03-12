/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hanlder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42.madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:05:55 by jdorazio          #+#    #+#             */
/*   Updated: 2025/01/09 16:05:55 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	exit_handler(int n_exit)
{
	if (n_exit == 1)
		ft_putstr_fd("Input infile 'command 1' 'command2' outfile\n", 1);
	else if (n_exit == 2)
		perror("Pipe Error\n");
	else if (n_exit == 3)
		perror("Fork Error\n");
	else if (n_exit == 4)
		perror("Infile Missing\n");
	else if (n_exit == 5)
		printf("Error splitting command\n");
	else if (n_exit == 6)
		perror("Command not found\n");
	else if (n_exit == 7)
		perror("Command not executed\n");
	exit(EXIT_FAILURE);
}

char	*get_command_path(char *cmd, char **env)
{
	char	**paths;
	char	*temp;
	char	*full_path;
	int		i;

	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	paths = ft_split(ft_getenv("PATH", env), ':');
	i = 0;
	while (paths[++i])
	{
		temp = ft_strjoin("/", cmd);
		full_path = ft_strjoin(paths[i], temp);
		free(temp);
		if (access(full_path, X_OK) == 0)
		{
			ft_free_array(paths);
			return (full_path);
		}
		free(full_path);
	}
	return (ft_free_array(paths), NULL);
}

char	*ft_getenv(const char *name, char **env)
{
	size_t	len;
	int		i;

	i = 0;
	len = ft_strlen(name);
	while (env[i])
	{
		if (ft_strncmp(env[i], name, len) == 0 && env[i][len] == '=')
			return (&env[i][len + 1]);
		i++;
	}
	return (NULL);
}

// char	*ft_strjoin_three(const char *s1, const char *s2, const char *s3)
// {
// 	char	*temp;
// 	char	*result;

// 	temp = ft_strjoin(s1, s2);
// 	if (!temp)
// 		return (NULL);
// 	result = ft_strjoin(temp, s3);
// 	free(temp);
// 	return (result);
// }

void	ft_free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

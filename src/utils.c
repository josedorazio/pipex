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

void	exit_handler (int n_exit)
{
	if (n_exit == 1)
		printf("./pipex infile cmd cmd outfile \n");
	exit(n_exit);
}

char	*ft_getenv(char *name, char **env)
{
	int		i;
	size_t	len;

	len = ft_strlen(name);
	i = 0;
	while(env[i])
	{
		if (ft_strncmp(env[i], name, len) == 0 && env[i][len] == '=')
			return (&env[i][len + 1]);
		i++;
	}
	return (NULL);
}


char	*get_command_path(char*cmd, char **env)
{
	char	**paths;
	char	*path_var;
	char	*full_path;
	int		i;

	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	path_var = ft_getenv("PATH", env);
	if (!path_var)
		return NULL;
	paths = ft_split(path_var, ':');
	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin(ft_strjoin(paths[i], "/"), cmd);
		if (access(full_path, X_OK) == 0)
		{
			free(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free(paths);
	return (NULL);
}

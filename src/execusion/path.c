/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houabell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 00:47:33 by houabell          #+#    #+#             */
/*   Updated: 2025/06/12 01:27:46 by houabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*get_env_val(char *name, t_env *env)
{
	while (env)
	{
		if (ft_strcmp(env->key, name) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	*find_command_path(char *cmd, t_env *env)
{
	char	**dirs;
	char	*path_env;
	char	*cmd_path;
	char	*temp;
	int		i;

	path_env = get_env_val("PATH", env);
	if (!path_env)
		return (NULL);
	dirs = ft_split(path_env, ':');
	if (!dirs)
		return (NULL);
	i = 0;
	while (dirs[i])
	{
		temp = ft_strjoin(dirs[i], "/");
		cmd_path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (free_array(dirs), cmd_path);
		free(cmd_path);
		i++;
	}
	free_array(dirs);
	return (NULL);
}

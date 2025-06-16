/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houabell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 11:31:28 by houabell          #+#    #+#             */
/*   Updated: 2025/06/16 13:07:51 by houabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	update_pwd_vars(t_shell *shell)
{
	char	*oldpwd;
	char	*newpwd;
	t_env	*pwd_node;

	oldpwd = NULL;
	pwd_node = get_env_node(shell->env, "PWD");
	if (pwd_node && pwd_node->value)
	{
		oldpwd = ft_strdup(pwd_node->value);
		if (!oldpwd)
			return (1);
		update_env_var(shell, "OLDPWD", oldpwd);
		free(oldpwd);
	}
	newpwd = getcwd(NULL, 0);
	if (!newpwd)
	{
		perror("cd: error retrieving current directory");
		return (1);
	}
	update_env_var(shell, "PWD", newpwd);
	free(newpwd);
	return (0);
}

static int	cd_to_oldpwd(t_shell *shell)
{
	t_env	*oldpwd_node;

	oldpwd_node = get_env_node(shell->env, "OLDPWD");
	if (!oldpwd_node || !oldpwd_node->value)
	{
		printf("minishell: cd: OLDPWD not set\n");
		return (1);
	}
	if (chdir(oldpwd_node->value) != 0)
	{
		printf("minishell: cd: %s: %s\n", oldpwd_node->value, strerror(errno));
		return (1);
	}
	printf("%s\n", oldpwd_node->value);
	return (0);
}

int	ft_cd(char **args, t_shell *shell)
{
	char	*path;
	t_env	*home_node;
	int		ret;

	if (args[1] && args[2])
		return (printf("minishell: cd: too many args\n"), 1);
	if (!args[1] || ft_strcmp(args[1], "~") == 0)
	{
		home_node = get_env_node(shell->env, "HOME");
		if (!home_node || !home_node->value)
			return (printf("minishell: cd: HOME not set\n"), 1);
		path = home_node->value;
	}
	else if (ft_strcmp(args[1], "-") == 0)
		return ((cd_to_oldpwd(shell) || update_pwd_vars(shell)));
	else
		path = args[1];
	if (chdir(path) != 0)
	{
		printf("minishell: cd: %s: %s\n", path, strerror(errno));
		return (1);
	}
	ret = update_pwd_vars(shell);
	return (ret);
}

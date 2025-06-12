/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houabell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 01:58:19 by houabell          #+#    #+#             */
/*   Updated: 2025/06/12 02:15:42 by houabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
		return (perror("pwd"), 1);
	printf("%s\n", path);
	free(path);
	return (0);
}

int	ft_env(t_shell *shell)
{
	t_env	*current;

	current = shell->env;
	while (current)
	{
		if (current->value)
			printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
	return (0);
}

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "echo") == 0 || \
			ft_strcmp(cmd, "cd") == 0 || \
			ft_strcmp(cmd, "pwd") == 0 || \
			ft_strcmp(cmd, "export") == 0 || \
			ft_strcmp(cmd, "unset") == 0 || \
			ft_strcmp(cmd, "env") == 0 || \
			ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

int	ft_echo(char **args)
{
	int	i;
	int	newline_flag;

	i = 1;
	newline_flag = 1;
	while (args[i] && ft_strcmp(args[i], "-n") == 0)
	{
		newline_flag = 0;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (newline_flag)
		printf("\n");
	return (0);
}

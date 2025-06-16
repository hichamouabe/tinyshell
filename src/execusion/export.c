/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houabell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:25:53 by houabell          #+#    #+#             */
/*   Updated: 2025/06/16 14:05:08 by houabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	handle_export_arg(char *arg, t_shell *shell)
{
	char	*key;
	char	*val;
	char	*eq;

	if (!is_valid_identifier(arg))
	{
		printf("minishell: export: '%s': not a valid identifer\n", arg);
		return (1);
	}
	eq = ft_strchr(arg, '=');
	if (eq)
	{
		key = ft_strndup(arg, eq - arg);
		val = ft_strdup(eq + 1);
		update_env_var(shell, key, val);
		free(val);
	}
	else
	{
		key = ft_strdup(arg);
		update_env_var(shell, key, NULL);
	}
	free(key);
	return (0);
}

int	ft_export(char **args, t_shell *shell)
{
	int	i;
	int	ret;

	i = 1;
	ret = 0;
	if (!args[1])
		return (print_export(shell), 0);
	while (args[i])
	{
		if (handle_export_arg(args[i], shell))
			ret = 1;
		i++;
	}
	return (ret);
}

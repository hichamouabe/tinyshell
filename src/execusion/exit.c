/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houabell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 11:19:07 by houabell          #+#    #+#             */
/*   Updated: 2025/06/16 11:28:51 by houabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_str_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(char **args, t_shell *shell)
{
	long	exit_code;

	printf("exit\n");
	if (!args[1])
	{
		shell->running = 0;
		return (shell->exit_status);
	}
	if (!is_str_numeric(args[1]))
	{
		printf("minishell: exit: %s: numeric arg required\n", args[1]);
		shell->exit_status = 2;
		shell->running = 0;
		return (2);
	}
	if (args[2])
	{
		printf("minishell: exit: too many args\n");
		return (1);
	}
	exit_code = ft_atoi(args[1]);
	shell->exit_status = exit_code;
	shell->running = 0;
	return (shell->exit_status);
}

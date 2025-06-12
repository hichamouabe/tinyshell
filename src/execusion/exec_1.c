/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houabell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 02:16:48 by houabell          #+#    #+#             */
/*   Updated: 2025/06/12 02:20:15 by houabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	execute_builtin(t_command *cmd, t_shell *shell)
{
	char	*cmd_name;

	cmd_name = cmd->args[0];
	if (ft_strcmp(cmd_name, "pwd") == 0)
		return (ft_pwd());
	if (ft_strcmp(cmd_name, "env") == 0)
		return (ft_env(shell));
	if (ft_strcmp(cmd_name, "echo") == 0)
		return (ft_echo(cmd->args));
	return (1);
}

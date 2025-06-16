/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houabell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 02:16:48 by houabell          #+#    #+#             */
/*   Updated: 2025/06/16 14:00:36 by houabell         ###   ########.fr       */
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
	if (ft_strcmp(cmd_name, "export") == 0)
		return (ft_export(cmd->args, shell));
	if (ft_strcmp(cmd_name, "unset") == 0)
		return (ft_unset(cmd->args, shell));
	if (ft_strcmp(cmd_name, "cd") == 0)
		return (ft_cd(cmd->args, shell));
	if (ft_strcmp(cmd_name, "exit") == 0)
		return (ft_exit(cmd->args, shell));
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houabell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 00:57:59 by houabell          #+#    #+#             */
/*   Updated: 2025/06/18 13:56:15 by houabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	count_env_nodes(t_env *env)
{
	t_env	*tmp;
	int		count;

	count = 0;
	tmp = env;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

static char	*create_env_entry(t_env *node)
{
	char	*key_val_join;
	char	*result;

	key_val_join = ft_strjoin(node->key, "=");
	if (!key_val_join)
		return (NULL);
	result = ft_strjoin(key_val_join, node->value);
	free(key_val_join);
	return (result);
}

static char	**env_list_to_array(t_env *env)
{
	t_env	*tmp;
	char	**array;
	int		count;
	int		i;

	count = count_env_nodes(env);
	array = malloc(sizeof(char *) * (count + 1));
	if (!array)
		return (NULL);
	i = 0;
	tmp = env;
	while (tmp)
	{
		array[i] = create_env_entry(tmp);
		if (!array[i])
			return (NULL);
		i++;
		tmp = tmp->next;
	}
	array[i] = NULL;
	return (array);
}

void	execute_external(t_command *cmd, t_shell *shell)
{
	char	*path;
	char	**envp;

	if (ft_strchr(cmd->args[0], '/'))
		path = ft_strdup(cmd->args[0]);
	else
		path = find_command_path(cmd->args[0], shell->env);
	if (!path || access(path, F_OK) != 0)
	{
		printf("minishell: %s: command not found\n", cmd->args[0]);
		free(path);
		exit(127);
	}
	envp = env_list_to_array(shell->env);
	printf("--- [DEBUG] Executing: %s ---\n", path);
	execve(path, cmd->args, envp);
	perror("minishell");
	free(path);
	free_array(envp);
	exit(126);
}

void	execute_single_command(t_shell *shell)
{
	t_command	*cmd;
	pid_t		pid;
	int		original_fds[2];

	cmd = shell->commands;
	if (!cmd || !cmd->args || !cmd->args[0])
		return (restore_io(original_fds));
	if (handle_redirections(cmd, original_fds) != 0)
	{
		shell->exit_status = 1;
		restore_io(original_fds);
		return ;
	}
	if (is_builtin(cmd->args[0]))
	{
		shell->exit_status = execute_builtin(cmd, shell);
		restore_io(original_fds);
		return ;
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		shell->exit_status = 1;
		return ;
	}
	if (pid == 0)
		execute_external(cmd, shell);
	else
	{
		waitpid(pid, &shell->exit_status, 0);
		if (WIFEXITED(shell->exit_status))
			shell->exit_status = WEXITSTATUS(shell->exit_status);
	}
	restore_io(original_fds);
}

void	execute_commands(t_shell *shell)
{
	t_command	*cmd;

	cmd = shell->commands;
	if (!cmd)
		return ;
	if (cmd->next == NULL)
		execute_single_command(shell);
	else
		printf("--------pipes called bro");
}

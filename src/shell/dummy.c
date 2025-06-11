/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dummy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houabell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 02:03:04 by houabell          #+#    #+#             */
/*   Updated: 2025/06/04 02:06:41 by houabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// File: src/shell/shell_commands_dummy.c
// (You can place these in an existing file in src/shell or a new one)

/**
 * @brief Dummy function for creating commands.
 *
 * This function is a placeholder and does not actually parse tokens
 * into commands. It's here to allow the rest of the shell logic
 * (like tokenization and expansion) to be tested without a full parser.
 *
 * @param shell The shell structure, which would normally contain tokens
 *              to be parsed and would be populated with commands.
 */


/**
 * @brief Dummy function for executing commands.
 *
 * This function is a placeholder and does not actually execute any commands.
 * It's here to complete the shell loop structure for testing other phases.
 *
 * @param shell The shell structure, which would normally contain commands
 *              to be executed.
 */
void execute_commands(t_shell *shell)
{
	// To avoid unused parameter warnings
	(void)shell;

	// In a real implementation, this function would:
	// 1. Iterate through shell->commands.
	// 2. For each command:
	//    a. Handle pipes if present.
	//    b. Set up redirections.
	//    c. Fork processes for external commands.
	//    d. Execute built-in commands directly.
	//    e. Manage file descriptors.
	//    f. Wait for child processes.
	//    g. Update shell->exit_status.
	// printf("DEBUG: excute_commands (dummy) called.\n");
	if (shell && shell->commands)
	{
		// A very basic "acknowledgement" that there might be commands.
		// You could print the first command's first arg if it exists,
		// but since create_commands is also a dummy, shell->commands might be NULL
		// or uninitialized.
	}
}

/**
 * @brief Dummy function for freeing command structures.
 *
 * This function is a placeholder. In a real implementation, it would
 * iterate through a list of t_command structures and free all allocated
 * memory, including the argument arrays and redirection lists.
 *
 * @param commands A pointer to the head of the command list.
 */
static const char	*redirect_type_to_string(t_token_type type)
{
	if (type == TOKEN_REDIR_IN)
		return ("< (IN)");
	if (type == TOKEN_REDIR_OUT)
		return ("> (OUT)");
	if (type == TOKEN_REDIR_APPEND)
		return (">> (APPEND)");
	if (type == TOKEN_HEREDOC)
		return ("<< (HEREDOC)");
	return ("UNKNOWN REDIR");
}

/**
 * @brief Prints the parsed command list for debugging.
 */
void	print_commands(t_command *commands)
{
	t_command	*current_cmd;
	t_redirect	*current_redir;
	int			i;
	int			j;

	printf("\n--- Parsed Commands ---\n");
	current_cmd = commands;
	i = 0;
	if (!current_cmd)
	{
		printf("(no commands parsed)\n");
		printf("-----------------------\n\n");
		return ;
	}
	while (current_cmd)
	{
		printf("Command %d:\n", i++);
		j = 0;
		while (current_cmd->args && current_cmd->args[j])
		{
			printf("  Arg[%d]: [%s]\n", j, current_cmd->args[j]);
			j++;
		}
		if (j == 0)
			printf("  (no arguments)\n");
		current_redir = current_cmd->redirects;
		if (!current_redir)
			printf("  (no redirections)\n");
		else
		{
			printf("  Redirections:\n");
			while (current_redir)
			{
				printf("    - Type: %-15s File: [%s]\n",
					redirect_type_to_string(current_redir->type),
					current_redir->file);
				current_redir = current_redir->next;
			}
		}
		current_cmd = current_cmd->next;
		if (current_cmd)
			printf("  | (pipe to next command)\n");
	}
	printf("-----------------------\n\n");
}

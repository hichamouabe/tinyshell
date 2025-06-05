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
void create_commands(t_shell *shell)
{
	// To avoid unused parameter warnings
	(void)shell;

	// In a real implementation, this function would:
	// 1. Iterate through shell->tokens.
	// 2. Group tokens into t_command structures.
	// 3. Populate command arguments (char **args).
	// 4. Populate command redirections (t_redirect *redirects).
	// 5. Link t_command structures into a list (shell->commands).
	// printf("DEBUG: create_commands (dummy) called.\n");
}

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
void free_commands(t_command *commands)
{
	// To avoid unused parameter warnings
	(void)commands;

	// In a real implementation, this function would:
	// t_command *current = commands;
	// t_command *next_cmd;
	// while (current)
	// {
	//     next_cmd = current->next;
	//     // Free current->args (it's a char **, so free each string then the array)
	//     if (current->args)
	//     {
	//         for (int i = 0; current->args[i]; i++)
	//             free(current->args[i]);
	//         free(current->args);
	//     }
	//     // Free current->redirects (iterate through the t_redirect list)
	//     t_redirect *redir = current->redirects;
	//     t_redirect *next_redir;
	//     while (redir)
	//     {
	//         next_redir = redir->next;
	//         if (redir->file)
	//             free(redir->file);
	//         free(redir);
	//         redir = next_redir;
	//     }
	//     free(current);
	//     current = next_cmd;
	// }
	// printf("DEBUG: free_commands (dummy) called.\n");
}

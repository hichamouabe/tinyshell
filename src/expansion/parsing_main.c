/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houabell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:17:07 by houabell          #+#    #+#             */
/*   Updated: 2025/06/21 16:29:53 by houabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_command	*parse_tokens(t_shell	*shell)
{
	if (shell && shell->tokens)
	{
		if (shell->variables)
		{
			print_variables(shell->variables);
			expand_variables(shell);
			if (!shell->variables)
				return (NULL);
			print_tokens(shell->tokens);
		}
		if (check_ambig(shell) != SUCCESS)
			return (NULL);
		if (handle_heredocs(shell) != SUCCESS)
			return (NULL);
		printf("--- [DEBUG] the tokens after the heredoc function processing: ---\n");
		print_tokens(shell->tokens);
		// --> hna asat ghadi t9ad commands linked list btari9tk
		printf("--- [DEBUG] final parsed commands: ---\n");
		create_commands(shell);
		print_commands(shell->commands);
		return (shell->commands);
	}
	return (NULL);
}

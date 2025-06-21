/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houabell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 01:57:51 by houabell          #+#    #+#             */
/*   Updated: 2025/06/21 16:21:41 by houabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_redirection_syntax(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (is_redirection(current->type))
		{
			if (!current->next || current->next->type != TOKEN_WORD)
			{
				printf("minishell: syntax error near unexpected token `%s'\n",
					current->value);
				return (0);
			}
		}
		current = current->next;
	}
	return (1);
}

int	check_pipe_syntax(t_token *tokens)
{
	t_token	*current;
	int		is_first;

	current = tokens;
	is_first = 1;
	while (current)
	{
		if (current->type == TOKEN_PIPE)
		{
			if (is_first)
			{
				printf("minishell: syntax error near unexpected token '|'\n");
				return (0);
			}
			if (!current->next || current->next->type == TOKEN_PIPE)
			{
				printf("minishell: syntax error near unexpected token '|'\n");
				return (0);
			}
		}
		current = current->next;
		is_first = 0;
	}
	return (1);
}

/*int	check_ambig(t_shell *shell)
{
	t_token	*current;
	t_token	*prev;

	current = shell->tokens;
	prev = NULL;
	while (current)
	{
		if (prev && is_redirection(prev->type) && current->value[0] == '\0')
		{
			printf("minishell: No such file or directory\n");
			shell->exit_status = 1;
			return (ERROR);
		}
		if (current->is_from_redir && current->next && \
					current->next->is_from_redir)
		{
			printf("minishell: ambiguous redirect\n");
			shell->exit_status = 1;
			return (ERROR);
		}
		prev = current;
		current = current->next;
	}
	return (SUCCESS);
}*/
int	check_ambig(t_shell *shell)
{
	t_token	*current;

	current = shell->tokens;
	while (current)
	{
		if (is_redirection(current->type))
		{
			// Case 1: Redirection at the very end (e.g., "ls >")
			if (!current->next)
			{
				printf("minishell: syntax error near unexpected token `newline'\n");
				shell->exit_status = 2;
				return (ERROR);
			}
			// Case 2: Filename token is not a WORD (e.g., "ls > |")
			if (current->next->type != TOKEN_WORD)
			{
				printf("minishell: syntax error near unexpected token `%s'\n",
					current->next->value);
				shell->exit_status = 2;
				return (ERROR);
			}
			// Case 3: Ambiguous redirect after expansion (e.g., ls > $var where var="a b")
			// We check if the token after the redirection came from an expansion that produced more than one word.
			if (current->next->is_from_redir && current->next->next && current->next->next->is_from_redir)
			{
				printf("minishell: ambiguous redirect\n");
				shell->exit_status = 1;
				return (ERROR);
			}
		}
		current = current->next;
	}
	return (SUCCESS);
}

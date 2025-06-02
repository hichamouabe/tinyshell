/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houabell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:09:56 by houabell          #+#    #+#             */
/*   Updated: 2025/05/30 00:11:37 by houabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	has_variable(t_token *token)
{
	int	i;

	i = 0;
	while (token->value[i])
	{
		if (token->value[i] == '$' && is_allowed(token->value[i + 1]))
			return (1);
		i++;
	}
	return (0);
}

void	process_each_token(t_token **token, t_var_info **var, t_shell *shell)
{
	char	**segments;
	t_token	*new_list;
	t_token	*first_to_free;

	segments = expand_token_value((*token)->value, var, shell);
	if (!segments || !segments[0])
		return ;
	new_list = create_token_list(segments);
	if (!new_list)
		return ;
	first_to_free = new_list;
	replace_first_token(*token, new_list);
	insert_remaining_tokens(*token, new_list);
	free(first_to_free->value);
	free(first_to_free);
	free(segments);
}

void	expand_variables(t_shell *shell)
{
	t_token		*current_tok;
	t_var_info	*current_var;

	current_tok = shell->tokens;
	current_var = shell->variables;
	while (current_tok && current_var)
	{
		if (current_tok->type == TOKEN_WORD && has_variable(current_tok))
			process_each_token(&current_tok, &current_var, shell);
		else
			current_tok = current_tok->next;
	}
}

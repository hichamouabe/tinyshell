/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houabell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 00:06:03 by houabell          #+#    #+#             */
/*   Updated: 2025/05/12 15:55:59 by houabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_token	*get_next_token_from_input(char *input, int *i, t_shell *shell)
{
	t_token	*new;

	if (is_special(input[*i]))
		new = handle_special(input, i);
	else
		new = handle_word(input, i);
	return (new);
}

t_token	*tokenize(char *input, t_shell *shell)
{
	t_token	*tokens;
	t_token	*new;
	int		i;

	tokens = NULL;
	i = 0;
	while (input[i])
	{
		while (input[i] && is_whitespace(input[i]))
			i++;
		if (input[i] == '\0')
			break ;
		new = get_next_token_from_input(input, &i, shell);
		if (!new)
			return (free_tokens(tokens), NULL);
		add_token(&tokens, new);
	}
	return (tokens);
}

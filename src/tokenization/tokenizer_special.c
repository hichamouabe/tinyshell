/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_special.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houabell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 01:06:07 by houabell          #+#    #+#             */
/*   Updated: 2025/05/11 01:10:35 by houabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_token	*handle_pipe(char *input, int *i)
{
	t_token	*token;

	token = NULL;
	if (input[*i] == '|')
	{
		token = new_token(TOKEN_PIPE, "|", QUOTE_NONE);
		(*i)++;
	}
	return (token);
}

static t_token	*handle_redir_in(char *input, int *i)
{
	t_token	*token;

	token = NULL;
	if (input[*i] == '<')
	{
		if (input[*i + 1] == '<')
		{
			token = new_token(TOKEN_HEREDOC, "<<", QUOTE_NONE);
			(*i) += 2;
		}
		else
		{
			token = new_token(TOKEN_REDIR_IN, "<", QUOTE_NONE);
			(*i)++;
		}
	}
	return (token);
}

static t_token	*handle_redir_out(char *input, int *i)
{
	t_token	*token;

	token = NULL;
	if (input[*i] == '>')
	{
		if (input[*i + 1] == '>')
		{
			token = new_token(TOKEN_REDIR_APPEND, ">>", QUOTE_NONE);
			(*i) += 2;
		}
		else
		{
			token = new_token(TOKEN_REDIR_OUT, ">", QUOTE_NONE);
			(*i)++;
		}
	}
	return (token);
}

t_token	*handle_special(char *input, int *i)
{
	t_token	*token;

	token = NULL;
	if (input[*i] == '|')
		token = handle_pipe(input, i);
	else if (input[*i] == '<')
		token = hande_redir_in(input, i);
	else if (input[*i] == '<')
		token = handle_redir_out(input, i);
	else
		return (NULL);
	return (token);
}

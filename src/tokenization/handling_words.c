/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houabell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 00:15:01 by houabell          #+#    #+#             */
/*   Updated: 2025/05/18 09:32:38 by houabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	handle_quoted_part(t_quote_params *params)
{
	char	*quoted_content;
	char	*new_word;

	quoted_content = NULL;
	if (append_segment_to_word(params->input, *(params->start), \
				*(params->i), params->word) == -1)
		return (-1);
	if (!handle_quotes(params->input, params->i, &quoted_content))
		return (-1);
	log_expandable(params->shell, quoted_content);
	new_word = append_str(*(params->word), quoted_content);
	free(quoted_content);
	if (!new_word)
		return (-1);
	*(params->word) = new_word;
	*(params->start) = *(params->i);
	return (0);
}

static int	handle_quote_in_word(char *input, int *i, int *start, \
		t_word_context *ctx)
{
	t_quote_params	params;

	if (input[*i] == '\'')
		ctx->shell->csqt = QUOTE_SINGLE;
	else
		ctx->shell->csqt = QUOTE_DOUBLE;
	params.input = input;
	params.i = i;
	params.start = start;
	params.word = &(ctx->word);
	params.shell = ctx->shell;
	if (handle_quoted_part(&params) == -1)
	{
		free(ctx->word);
		return (-1);
	}
	return (0);
}

static void	init_word_context(t_word_context *ctx, t_shell *shell)
{
	ctx->word = ft_strdup("");
	ctx->token = NULL;
	ctx->shell = shell;
}

static t_token	*finalize_word(char *input, int start, int *i, \
		t_word_context *ctx)
{
	char	*var_i_think;
	t_token	*result;

	var_i_think = ft_strndup(input + start, *i - start);
	log_expandable(ctx->shell, var_i_think);
	if (append_segment_to_word(input, start, *i, &(ctx->word)) == -1)
	{
		free(ctx->word);
		free(var_i_think);
		return (NULL);
	}
	result = new_token(TOKEN_WORD, ctx->word);
	free(ctx->word);
	free(var_i_think);
	return (result);
}

t_token	*handle_word(char *input, int *i, t_shell *shell)
{
	int		start;
	t_word_context	ctx;

	init_word_context(&ctx, shell);
	if (!ctx.word)
		return (NULL);
	start = *i;
	while (input[*i] && !is_whitespace(input[*i]) && \
			!is_special(input[*i]))
	{
		if (input[*i] == '\'' || input[*i] == '"')
		{
			if (handle_quote_in_word(input, i, &start, &ctx) == -1)
				return (NULL);
		}
		else
			(*i)++;
	}
	return (finalize_word(input, start, i, &ctx));
}

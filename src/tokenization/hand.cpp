/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hand.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houabell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 00:15:01 by houabell          #+#    #+#             */
/*   Updated: 2025/06/05 17:46:25 by houabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	handle_quoted_part(t_quote_params *params, int expect_deli)
{
	char	*quoted_content;
	char	*new_word;

	quoted_content = NULL;
	if (append_segment_to_word(params->input, *(params->start), \
				*(params->i), params->word) == -1)
		return (-1);
	if (!handle_quotes(params->input, params->i, &quoted_content))
		return (-1);
	if (!expect_deli)
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
	if (handle_quoted_part(&params, (ctx->expect_delimiter)) == -1)
	{
		free(ctx->word);
		return (-1);
	}
	ctx->shell->csqt = QUOTE_NONE;
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
	if (!ctx->expect_delimiter && var_i_think)
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
int	segment_has_any_actual_quotes(const char *segment_str, int len)
{
	int	k;

	k = 0;
	while (k < len)
	{
		if (segment_str[k] == '\'' || segment_str[k] == '"')
			return (1);
		k++;
	}
	return (0);
}

static int	prepare_unquoted_segment(char *input, int start_seg, int *i, t_word_context *ctx)
{
	char	*unquoted_seg;

	unquoted_seg = ft_strndup(input + start_seg, *i - start_seg);
	if (!unquoted_seg)
	{
		free(ctx->word);
		return (-1);
	}
	if (!ctx->expect_delimiter)
	{
		ctx->shell->csqt = QUOTE_NONE;
		log_expandable(ctx->shell, unquoted_seg);
	}
	free(unquoted_seg);
	return (0);
}

static int	process_word_loop(char *input, int *i, int *start_seg, t_word_context *ctx)
{
	while (input[*i] && !is_whitespace(input[*i]) && !is_special(input[*i]))
	{
		if (input[*i] == '\'' || input[*i] == '"')
		{
			if (*i > *start_seg)
			{
				if (prepare_unquoted_segment(input, *start_seg, i, ctx) == -1)
					return (-1);
			}
			if (handle_quote_in_word(input, i, start_seg, ctx) == -1)
				return (-1);
		}
		else
			(*i)++;
	}
	return (0);
}

static t_token	*finish_word_token(t_word_state *state, t_word_context *ctx)
{
	t_token	*final_token;

	ctx->shell->csqt = QUOTE_NONE;
	final_token = finalize_word(state->input, state->start_seg, state->i, ctx);
	if (final_token && ctx->expect_delimiter)
	{
		final_token->is_heredoc_delimiter_value = 1;
		final_token->original_delimiter_had_quotes =
			segment_has_any_actual_quotes(
				state->input + state->start_word,
				*(state->i) - state->start_word
			);
	}
	return (final_token);
}

t_token	*handle_word(char *input, int *i, t_shell *shell, int expect_delimiter)
{
	t_word_context	ctx;
	t_word_state	state;

	init_word_context(&ctx, shell);
	ctx.expect_delimiter = expect_delimiter;
	if (!ctx.word)
		return (NULL);

	state.input = input;
	state.start_word = *i;
	state.start_seg = *i;
	state.i = i;

	if (process_word_loop(input, i, &state.start_seg, &ctx) == -1)
		return (NULL);

	return (finish_word_token(&state, &ctx));
}

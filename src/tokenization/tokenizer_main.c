/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houabell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 00:06:03 by houabell          #+#    #+#             */
/*   Updated: 2025/06/02 02:24:21 by houabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_token	*get_next_token_from_input(char *input, int *i, t_shell *shell)
{
	t_token	*new;

	if (is_special(input[*i]))
		new = handle_special(input, i);
	else
		new = handle_word(input, i, shell);
	return (new);
}

char	*append_str(char *str, char *append)
{
	char	*result;
	size_t	len1;
	size_t	len2;

	if (!str)
		return (ft_strdup(append));
	if (!append)
		return (str);
	len1 = ft_strlen(str);
	len2 = ft_strlen(append);
	result = (char *)malloc(len1 + len2 + 1);
	if (!result)
	{
		free(result);
		return (NULL);
	}
	ft_strcpy(result, str);
	ft_strcat(result, append);
	free(str);
	return (result);
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

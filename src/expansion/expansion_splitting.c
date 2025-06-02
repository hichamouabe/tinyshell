/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_splitting.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houabell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 22:08:47 by houabell          #+#    #+#             */
/*   Updated: 2025/05/31 22:19:16 by houabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	process_word_splitting(t_expansion_state *state, char *expanded)
{
	char	**split;

	split = ft_split(expanded, ' ');
	if (split)
		distribute_split_words(state, split);
	else if (*expanded)
		state->buffer = ft_strdup(expanded);
}

void	distribute_split_words(t_expansion_state *state, char **split)
{
	int	j;

	j = 0;
	while (split[j])
	{
		if (split[j + 1] == NULL && *split[j])
			state->buffer = ft_strdup(split[j]);
		else if (*split[j])
			add_segment(&state->result, ft_strdup(split[j]));
		j++;
	}
	free_array(split);
}

void	flush_buffer_to_result(t_expansion_state *state)
{
	if (state->buffer && *state->buffer)
	{
		add_segment(&state->result, ft_strdup(state->buffer));
		free(state->buffer);
		state->buffer = NULL;
	}
}

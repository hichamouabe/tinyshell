/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_splitting.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houabell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 22:08:47 by houabell          #+#    #+#             */
/*   Updated: 2025/06/02 22:59:16 by houabell         ###   ########.fr       */
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

/*void	distribute_split_words(t_expansion_state *state, char **split)
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
}*/

void	distribute_split_words(t_expansion_state *state, char **split)
{
	int		j;
	char	*first_word_processed; // This will hold the (possibly joined) first word

	if (!split || !split[0] || !*(split[0]))
	{
		if (split) free_array(split);
		return;
	}

	if (state->buffer && *(state->buffer))
	{
		first_word_processed = ft_strjoin(state->buffer, split[0]);
		free(state->buffer); 
		state->buffer = NULL;
		if (!first_word_processed) { free_array(split); return; }
	}
	else
	{
		first_word_processed = ft_strdup(split[0]); // Make a copy, as original split[0] will be freed by free_array
		if (!first_word_processed) { free_array(split); return; }
	}

	if (split[1] == NULL) // If original 'split' had only one word
	{
		if (state->buffer) free(state->buffer); // Should be NULL if join happened
		state->buffer = first_word_processed; // Ownership of first_word_processed transferred to state->buffer
	}
	else // Original 'split' had more than one word
	{
		add_segment(&state->result, first_word_processed); // add_segment takes ownership of first_word_processed
		// DO NOT free first_word_processed here
	}

	j = 1;
	while (split[j])
	{
		if (split[j + 1] == NULL) // Last of the remaining original split words
		{
			if (state->buffer) free(state->buffer);
			state->buffer = ft_strdup(split[j]); // Make a copy for the buffer
            if (!state->buffer && split[j] && *split[j]) { /* Malloc error */ }
		}
		else // Intermediate of the remaining original split words
		{
			add_segment(&state->result, ft_strdup(split[j])); // Make a copy for add_segment
		}
		j++;
	}
	free_array(split); // Frees the 'split' structure and the original strings it pointed to
}

/*void	flush_buffer_to_result(t_expansion_state *state)
{
	if (state->buffer && *state->buffer)
	{
		add_segment(&state->result, ft_strdup(state->buffer));
		free(state->buffer);
		state->buffer = NULL;
	}
}*/

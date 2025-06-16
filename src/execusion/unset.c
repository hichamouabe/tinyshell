/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houabell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:37:48 by houabell          #+#    #+#             */
/*   Updated: 2025/06/16 14:04:32 by houabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	remove_env_var(t_shell *shell, char *key)
{
	t_env	*curr;
	t_env	*prev;

	prev = NULL;
	curr = shell->env;
	while (curr != NULL && ft_strcmp(curr->key, key) != 0)
	{
		prev = curr;
		curr = curr->next;
	}
	if (curr != NULL)
	{
		if (prev == NULL)
			shell->env = curr->next;
		else
			prev->next = curr->next;
		free(curr->key);
		if (curr->value)
			free(curr->value);
		free(curr);
	}
}

int	ft_unset(char **args, t_shell *shell)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
			printf("minishell: unset: '%s': not valid identifier\n", args[i]);
		else
			remove_env_var(shell, args[i]);
		i++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houabell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:17:07 by houabell          #+#    #+#             */
/*   Updated: 2025/06/02 02:42:44 by houabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


t_command	*parse_tokens(t_shell	*shell)
{
	if (shell && shell->tokens)
	{
		if (shell->variables)
		{
			print_variables(shell->variables);
			expand_variables(shell);
			print_tokens(shell->tokens);
		}
		create_commands(shell);
		return (shell->commands);
	}
	return (NULL);
}

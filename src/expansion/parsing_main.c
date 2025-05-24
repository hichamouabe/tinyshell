/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houabell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:17:07 by houabell          #+#    #+#             */
/*   Updated: 2025/05/23 16:44:00 by houabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


void	expand_variable(t_shell *shell)
{

t_command	*parse_tokens(t_shell	*shell)
{
	if (shell && shell->tokens)
	{
		if (shell->variables)
			expand_variables(shell);
		create_commands(shell);
	}
}

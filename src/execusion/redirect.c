/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houabell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:39:44 by houabell          #+#    #+#             */
/*   Updated: 2025/06/17 11:42:17 by houabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	open_outfile(t_redirect *redir)
{
	int	fd;

	if (redir->type == TOKEN_REDIR_OUT)
		fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		printf("minishell: %s: %s\n", redir->file, strerror(errno));
		return (-1);
	}
	return (fd);
}

static int	handle_input_redir(t_redirect *redir, int *stdin_save)
{
	int	fd;

	fd = open(redir->file, O_RDONLY);
	if (fd == -1)
	{
		printf("minishell: %s: %s\n", redir->file, strerror(errno));
		return (1);
	}
	if (*stdin_save == -1)
		*stdin_save = dup(STDIN_FILENO);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

static int	handle_output_redir(t_redirect *redir, int *stdout_save)
{
	int	fd;

	fd = open_outfile(redir);
	if (fd == -1)
		return (1);
	if (*stdout_save == -1)
		*stdout_save = dup(STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	handle_redirections(t_command *cmd, int original_fds[2])
{
	t_redirect	*redir;

	redir = cmd->redirects;
	original_fds[0] = -1;
	original_fds[1] = -1;
	while (redir)
	{
		if (redir->type == TOKEN_REDIR_IN)
		{
			if (handle_input_redir(redir, &original_fds[0]))
				return (1);
		}
		else if (redir->type == TOKEN_REDIR_OUT || \
				redir->type == TOKEN_REDIR_APPEND)
		{
			if (handle_output_redir(redir, &original_fds[1]))
				return (1);
		}
		redir = redir->next;
	}
	return (0);
}

void	restore_io(int original_fds[2])
{
	if (original_fds[0] != -1)
	{
		dup2(original_fds[0], STDIN_FILENO);
		close(original_fds[0]);
	}
	if (original_fds[1] != -1)
	{
		dup2(original_fds[1], STDOUT_FILENO);
		close(original_fds[1]);
	}
}

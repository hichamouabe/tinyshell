#include "../../include/minishell.h"

// Helper to free a list of redirects
static void	free_redirects(t_redirect *redir)
{
	t_redirect	*tmp;

	while (redir)
	{
		tmp = redir->next;
		free(redir->file);
		free(redir);
		redir = tmp;
	}
}

// THIS IS THE FUNCTION YOU NEED TO ADD
void	free_commands(t_command *cmd)
{
	t_command	*tmp;

	while (cmd)
	{
		tmp = cmd->next;
		free_array(cmd->args); // Your existing free_array handles the char**
		free_redirects(cmd->redirects);
		free(cmd);
		cmd = tmp;
	}
}

// ... your other functions in this file (count_args_and_redirs, add_redirect)

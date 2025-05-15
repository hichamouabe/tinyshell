/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houabell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 04:51:41 by houabell          #+#    #+#             */
/*   Updated: 2025/05/15 00:08:46 by houabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <dirent.h>
# include <errno.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdbool.h>

# define SUCCESS 0
# define ERROR 1

typedef enum e_quote_type {
	QUOTE_NONE,
	QUOTE_SINGLE,
	QUOTE_DOUBLE
} t_quote_type;

typedef enum e_token_type {
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_HEREDOC,
	TOKEN_EOF
}	t_token_type;

typedef struct s_token {
	t_token_type	type;
	char	*value;
	t_quote_type	quote_status;
	struct s_token	*next;
}	t_token;

typedef struct	s_env {
	char	*key;
	char	*value;
	struct s_env	*next;
}	t_env;

typedef struct	s_var_info {
	char	*name;
	size_t	length;
	int	expandable;
	struct	s_var_info	*nex;
}	t_var_info;

typedef struct	s_redirect {
	t_token_type	type;
	char	*file;
	struct s_redirect	*next;
}	t_redirect;

typedef struct	s_command {
	char	**args;
	t_redirect	*redirects;
	struct s_command	*next;
}	t_command;

typedef struct	s_shell {
	t_token	*tokens;
	t_command	*commands;
	t_env	*env;
	int		exit_status;
	int		running;
	int	heredoc_sigint;
	char	*input;
	t_var_info	*variables;
}	t_shell;

typedef struct	s_exp_env {
	t_env	*env;
	int	status;
}	t_exp_env;

typedef struct	s_exp_state {
	t_token	**list_head;
	t_token	*current;
	t_token	*prev;
	t_env	*env;
	int	exit_status;
	bool	was_replaced;
}	t_exp_state;

typedef struct	s_quote_params {
	char	*input;
	int	*i;
	int	*start;
	char	**word;
	t_shell	*shell;
}	t_quote_params;

typedef struct s_word_context {
	char	*word;
	t_token	*token;
	t_quote_type	q_num;
	t_shell	*shell;
}	t_word_context;
#endif

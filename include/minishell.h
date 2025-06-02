/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houabell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 04:51:41 by houabell          #+#    #+#             */
/*   Updated: 2025/06/02 03:40:31 by houabell         ###   ########.fr       */
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
	t_quote_type	quote_context;
	struct	s_var_info	*next;
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
	t_quote_type	csqt;
}	t_shell;

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
	t_shell	*shell;
}	t_word_context;

typedef struct s_expansion_state
{
	char	**result;
	char	*buffer;
	int		i;
}	t_expansion_state;

extern volatile int g_signal_status; // Needs definition in a .c file

// Shell Core (src/shell)
t_shell			*init_shell(char **envp);
void			free_shell(t_shell *shell);
void			reset_shell(t_shell *shell);
int				minishell_loop(t_shell *shell);
int				validate_syntax(t_token *tokens);
void			free_var_info_list(t_var_info *var_head);
void			excute_commands(t_shell *shell); // Dummy for now
int				check_pipe_syntax(t_token *tokens); // Missing
int				check_redirection_syntax(t_token *tokens); // Missing
void			free_commands(t_command *commands); // Missing

// Tokenization (src/tokenization)
t_token			*tokenize(char *input, t_shell *shell);
t_token			*new_token(t_token_type type, char *value);
void			add_token(t_token **tokens, t_token *new);
void			free_tokens(t_token *tokens);
int				handle_quotes(char *input, int *i, char **value);
t_token			*handle_special(char *input, int *i);
t_token			*handle_word(char *input, int *i, t_shell *shell);
int				is_special(char c);
int				is_whitespace(char c);
int				is_redirection(t_token_type type);
int				ft_isalnum(char c); // Defined in tokenization/is_x.c
char			*append_str(char *str, char *append); // Defined in tokenization/tokenizer_main.c
int append_segment_to_word(char *input, int start, int current_i, char **word); // Static in is_x.c

void			print_tokens(t_token *tokens);

// Expansion (src/expansion)
t_command		*parse_tokens(t_shell *shell);
void			expand_variables(t_shell *shell);
void			create_commands(t_shell *shell); // Missing
char			**expand_token_value(char *str, t_var_info **var_list, t_shell *shell);
void			process_regular_text(char *str, t_expansion_state *state);
char			*extract_variable_name(char *str, t_expansion_state *state, t_var_info **var_list);
void			skip_regular_text(char *str, t_expansion_state *state);
void			process_variable_expansion(char *str, t_expansion_state *state, t_var_info **var_list, t_shell *shell);
void			apply_expansion_by_context(t_expansion_state *state, char *expanded_value, t_var_info **var_list);
void			handle_single_quote_context(t_expansion_state *state, char *expanded_value, t_var_info **var_list);
void			handle_double_quote_context(t_expansion_state *state, char *expanded_value);
void			handle_unquoted_context(t_expansion_state *state, char *expanded_value);
void			process_word_splitting(t_expansion_state *state, char *expanded);
void			distribute_split_words(t_expansion_state *state, char **split);
void			flush_buffer_to_result(t_expansion_state *state);
void			append_segment(char **buffer, char *part);
char			*get_env_value(char *name, t_shell *shell);
char			**ensure_valid_result(char **result);
void			add_segment(char ***result, char *segment);
void			copy_existing_segments(char **new_arr, char **old_arr, int count);
void			cleanup_expansion_step(char *var_name, char *expanded_value, t_var_info **var_list);
void			handle_extraction_failure(t_expansion_state *state, t_var_info **var_list); // Note: Original uses (*var_list)->value, should be name
void			handle_expansion_failure(t_expansion_state *state, char *var_name);  // Note: Original uses (*var_list)->value, should be name
int				has_variable(t_token *token);
void			process_each_token(t_token **token, t_var_info **var, t_shell *shell);
t_token			*create_token_list(char **segments);
t_token			*get_last_token(t_token *token_list);
void			replace_first_token(t_token *original, t_token *new_first);
void			insert_remaining_tokens(t_token *original, t_token *new_list);
char			*extract_var_name(char *str_after_dol, int *name_len); // From log_var_main.c
void			handle_question_mark(t_shell *shell, int *index); // From log_var_main.c (typo in original)
void			process_variable(t_shell *shell, char *segment, int *index); // From log_var_main.c
void			log_expandable(t_shell *shell, char *segment);
t_var_info		*create_var_node(char *name, t_quote_type context_csqt);
void			add_var_node(t_var_info **var_head, t_var_info *new_node);
void			free_var(t_var_info *var_head); // Defined in var_logging_utils.c, may or may not be used globally


void			print_variables(t_var_info *variables);

// Environment Handling (src/env_handling)
t_env			*init_env(char **envp);
void			free_env(t_env *env);
t_env			*new_env_node(char *key, char *value);
void			add_env_node(t_env **env, t_env *new);
t_env			*get_env_node(t_env *env, char *key);

// Signal Handling (src/signal_handling)
void			handle_signals(void);
void			sigint_handler(int sig);
void			sigquit_handler(int sig);
void			signint_heredoc_handler(int sig); // Typo in original name

// Utilities (src/utils)
size_t			ft_strlen(const char *s);
char			*ft_strdup(const char *s1);
char			*ft_strndup(const char *s1, size_t n);
char			*ft_strchr(const char *s, int c);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_itoa(int n);
char			**ft_split(char const *s, char c);
char			*ft_strjoin(char const *s1, char const *s2);
int				ft_isalpha(int c);
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t			ft_strlcpy(char *dst, const char *src, size_t destsize);
int				is_allowed(char c); // Defined in utils/str_stuff4.c
void			free_array(char **array);
char			*ft_strcpy(char *dst, const char *src); // Missing
char			*ft_strcat(char *dst, const char *src); // Missing
void			*ft_memcpy(void *dst, const void *src, size_t n); // Missing
#endif

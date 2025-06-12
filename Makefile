# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -lreadline

# Project Name
NAME = minishell

# Directories
INCLUDE_DIR = ./include/
SRC_DIR = ./src/
SHELL_DIR = $(SRC_DIR)shell/
TOKEN_DIR = $(SRC_DIR)tokenization/
EXP_DIR = $(SRC_DIR)expansion/
ENV_DIR = $(SRC_DIR)env_handling/
HEREDOC_DIR = $(SRC_DIR)heredoc/
PARSER_DIR = $(SRC_DIR)parser/
SIGNAL_DIR = $(SRC_DIR)signal_handling/
UTIL_DIR = $(SRC_DIR)utils/
EXEC_DIR = $(SRC_DIR)execusion/
# Source Files - ALL .c files must be listed here
SRCS = \
	$(SHELL_DIR)main.c \
	$(SHELL_DIR)shell_1.c \
	$(SHELL_DIR)shell_2.c \
	$(SHELL_DIR)check.c \
	$(SHELL_DIR)dummy.c \
	\
	$(TOKEN_DIR)tokenizer_main.c \
	$(TOKEN_DIR)tokenizer_core.c \
	$(TOKEN_DIR)tokenizer_special.c \
	$(TOKEN_DIR)handling_words.c \
	$(TOKEN_DIR)handling_words_utils.c \
	$(TOKEN_DIR)is_x.c \
	$(TOKEN_DIR)debug.c \
	\
	$(EXP_DIR)parsing_main.c \
	$(EXP_DIR)expanding_main.c \
	$(EXP_DIR)expand_token_value.c \
	$(EXP_DIR)expansion_process.c \
	$(EXP_DIR)expansion_context.c \
	$(EXP_DIR)expansion_splitting.c \
	$(EXP_DIR)distribute_split.c \
	$(EXP_DIR)expansion_error.c \
	$(EXP_DIR)process_each_token_utils.c \
	$(EXP_DIR)log_var_main.c \
	$(EXP_DIR)var_logging_utils.c \
	$(EXP_DIR)expansion_utils1.c \
	$(EXP_DIR)expansion_utils2.c \
	$(EXP_DIR)debug.c \
	\
	$(ENV_DIR)environement_main.c \
	$(ENV_DIR)environement_utils.c \
	\
	$(HEREDOC_DIR)handle_heredocs.c \
	$(HEREDOC_DIR)read_heredoc.c \
	$(HEREDOC_DIR)generate_heredoc_filename.c \
	$(HEREDOC_DIR)expand_heredoc_line.c \
	\
	$(PARSER_DIR)parser.c \
	$(PARSER_DIR)parser_utils.c \
	$(PARSER_DIR)parse_single_command.c \
	$(PARSER_DIR)free_stuff_brikolag.c \
	\
	$(SIGNAL_DIR)handle_signals.c \
	\
	$(UTIL_DIR)str_stuff1.c \
	$(UTIL_DIR)str_stuff2.c \
	$(UTIL_DIR)str_stuff3.c \
	$(UTIL_DIR)str_stuff4.c \
	$(UTIL_DIR)ft_split.c \
	\
	$(EXEC_DIR)execute.c \
	$(EXEC_DIR)path.c 

# Object Files - This automatically generates the list of .o files
OBJS = $(SRCS:.c=.o)

# --- THE RULES ---

# Default rule
all: $(NAME)

# Rule to link ALL object files into the final executable
$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)
	@echo "Minishell compiled!"

# Rule to compile any .c file into a .o file
# This is a pattern rule.
# -c means "compile only, don't link"
# -I tells the compiler where to find header files
%.o: %.c
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# --- CLEANUP RULES ---

clean:
	rm -f $(OBJS)
	@echo "Object files cleaned."

fclean: clean
	rm -f $(NAME)
	@echo "All cleaned."

re: fclean all

# Phony targets: these are not files
.PHONY: all clean fclean re

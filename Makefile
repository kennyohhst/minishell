NAME := minishell
NICKNAME := MINISHELL

# Directories
HDR_DIR := include
LIB_DIR := lib
SRC_DIR := src
OBJ_DIR := obj

# Compiler flags
CC := gcc
CFLAGS := -Wall -Werror -Wextra -g -fsanitize=address

# Includes
HDR_FILES :=	minishell.h

# Libft
LIBFT_DIR		:= $(LIB_DIR)/libft
LIB				:= $(LIBFT_DIR)/libft.a

# Files
SRC_FILES := \
				main.c							\
				signals.c						\
				utils.c							\
				env_list_create.c				\
				env_list_utils.c				\
				free_functions.c				\
\
				lexer/lexer.c					\
				lexer/quote_count.c				\
				lexer/tokens.c					\
				lexer/valid_pipe_check.c		\
				lexer/create_input_list.c		\
\
				parser/list_length.c			\
				parser/input_check_parse.c		\
				parser/parser.c					\
				parser/expander.c				\
				parser/malloc_functions.c		\
				test.c							\
\
				executor/execute.c				\
				executor/execute_utils.c		\
				executor/redirects.c			\
				executor/set_command_path.c		\
\
				executor/builtins/builtins.c	\
				executor/builtins/echo.c		\
				executor/builtins/pwd.c			\
				executor/builtins/env.c			\
				executor/builtins/cd.c			\
				executor/builtins/export.c		\
				executor/builtins/unset.c		\
				executor/builtins/exit.c		\

SRC := $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ := ${addprefix ${OBJ_DIR}/, ${SRC_FILES:.c=.o}}
HDR := $(addprefix $(HDR_DIR)/, $(HDR_FILES))

# Colours
GREEN	:= \033[32;1m
YELLOW	:= \033[33;1m
RED		:= \033[31;1m
BOLD	:= \033[1m
RESET	:= \033[0m

# Rules
all: ${NAME}

$(NAME): $(OBJ) $(LIB)
	@printf "%b%s%b" "$(YELLOW)$(BOLD)" "Compiling $(NICKNAME)..." "$(RESET)"
	@gcc $(CFLAGS) $(OBJ) $(LIB) -o $(NAME) -lreadline -L /Users/$(USER)/.brew/opt/readline/lib
	@printf "\t\t%b%s%b\n" "$(GREEN)$(BOLD)" "[OK]" "$(RESET)"

$(LIB):
	@make -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: src/%.c $(HDR)
	@mkdir -p obj
	@mkdir -p obj/lexer
	@mkdir -p obj/parser
	@mkdir -p obj/executor
	@mkdir -p obj/executor/builtins
	@gcc $(CFLAGS) -I $(HDR_DIR) -c $< -o $@ -I /Users/$(USER)/.brew/opt/readline/include

open: $(NAME)
	@./$(NAME)

log:
	git log --graph --format=format:'%C(bold blue)%h%C(reset) - %C(bold green)(%ar)%C(reset) %C(white)%an%C(reset)%C(bold yellow)%d%C(reset) %C(dim white)- %s%C(reset)' --all

test:
	tester/tester.py

norm:
	@norminette $(HDR_DIR) $(SRC)

clean:
	@echo "$(RED)$(BOLD)Cleaning $(NICKNAME)...$(RESET)"
	@rm -rf $(OBJ)
	@rm -rf $(OBJ_DIR)
	@make clean -C $(LIBFT_DIR)

fclean:
	@echo "$(RED)$(BOLD)Fully cleaning $(NICKNAME)...$(RESET)"
	@rm -rf ${NAME}
	@rm -rf $(OBJ)
	@rm -rf $(OBJ_DIR)
	@make fclean -C $(LIBFT_DIR)

re: fclean ${NAME}

.PHONY: all norminette clean fclean re
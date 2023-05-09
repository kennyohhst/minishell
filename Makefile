NAME := minishell
NICKNAME := MINISHELL

# Directories
HDR_DIR := include
LIB_DIR := lib
SRC_DIR := src
OBJ_DIR := obj

# Compiler flags
CC := gcc
CFLAGS := -Wall -Werror -Wextra -g # -fsanitize=address

# Includes
HDR_FILES :=	minishell.h

# Libft
LIBFT_DIR		:= $(LIB_DIR)/libft
LIB				:= $(LIBFT_DIR)/libft.a

# Files
SRC_FILES :=	main.c					\
				parse.c					\
				quote_count.c			\
				tokens.c				\
				valid_pipe_check.c		\
				list_functions.c		\
				get_command_path.c		\
				execute.c				\
				builtins.c				\

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
	@gcc $(CFLAGS) $(OBJ) $(LIB) -o $(NAME) -lreadline -I /Users/$(USER)/.brew/opt/readline/include -L/Users/$(USER)/.brew/opt/readline/lib
	@printf "\t\t%b%s%b\n" "$(GREEN)$(BOLD)" "[OK]" "$(RESET)"

$(LIB):
	@make -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: src/%.c $(HDR)
	@mkdir -p obj
	@gcc $(CFLAGS) -I $(HDR_DIR) -c $< -o $@ -I /Users/$(USER)/.brew/opt/readline/include

open: $(NAME)
	@./$(NAME)

log:
	git log --graph --format=format:'%C(bold blue)%h%C(reset) - %C(bold green)(%ar)%C(reset) %C(white)%an%C(reset)%C(bold yellow)%d%C(reset) %C(dim white)- %s%C(reset)' --all

norminette:
	@norminette $(SRC)

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
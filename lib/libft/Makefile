NAME		:= libft.a
NICKNAME	:= LIBFT

# Directories
LIBFT_DIR	:= src/libft
GNL_DIR		:= src/get_next_line
PRINTF_DIR	:= src/ft_printf

# Files
PRINTF		:=	$(PRINTF_DIR)/obj/*.o
GNL			:=	$(GNL_DIR)/obj/*.o
LIBFT		:=	$(LIBFT_DIR)/obj/*.o

# Colours
GREEN		:= \033[32;1m
YELLOW		:= \033[33;1m
RED			:= \033[31;1m
BOLD		:= \033[1m
RESET		:= \033[0m

# Rules
all: startmsg ${NAME}

$(NAME): $(PRINTF) $(GNL) $(LIBFT)
	@ar rc ${NAME} $^
	@printf "\t\t%b%s%b\n" "$(GREEN)$(BOLD)" "[OK]" "$(RESET)"

startmsg:
	@printf "%b%s%b" "$(YELLOW)$(BOLD)" "Compiling $(NICKNAME)..." "$(RESET)"

$(PRINTF):
	@make -C $(PRINTF_DIR)

$(GNL):
	@make -C $(GNL_DIR)

$(LIBFT):
	@make -C $(LIBFT_DIR)

clean:
	@echo "$(RED)$(BOLD)Cleaning $(NICKNAME)...$(RESET)"
	@make clean -C $(PRINTF_DIR)
	@make clean -C $(GNL_DIR)
	@make clean -C $(LIBFT_DIR)

fclean:
	@echo "$(RED)$(BOLD)Fully cleaning $(NICKNAME)...$(RESET)"
	@make fclean -C $(PRINTF_DIR)
	@make fclean -C $(GNL_DIR)
	@make fclean -C $(LIBFT_DIR)
	@rm -rf ${NAME}

re: fclean ${NAME}

.PHONY: all startmsg norminette clean fclean re

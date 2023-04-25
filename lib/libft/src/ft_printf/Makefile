NAME := ft_printf
NICKNAME := PRINTF

# Directories
HDR_DIR := ../../include
SRC_DIR := src
OBJ_DIR := obj

# Compiler flags
CC := gcc
CFLAGS := -Wall -Werror -Wextra

# Includes
HDR_FILES :=	ft_conversions.h		\
				ft_printf.h

# Files
SRC_FILES :=	ft_base_conversion.c	\
				ft_convert_nums.c		\
				ft_convert.c			\
				ft_printf.c				\

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
all: ${OBJ}

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HDR)
	@mkdir -p obj
	@gcc $(CFLAGS) -I $(HDR_DIR) -c $< -o $@

norminette:
	@norminette $(SRC)

clean:
	@rm -rf $(OBJ)
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -rf ${NAME}

re: fclean ${NAME}

.PHONY: all norminette clean fclean re

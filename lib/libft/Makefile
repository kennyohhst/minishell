NAME			:= libft.a
NICKNAME		:= LIBFT

# Directories
HDR_DIR			:= include
SRC_DIR			:= src
OBJ_DIR			:= obj

# Compiler flags
CC				:= gcc
CFLAGS			:= -Wall -Werror -Wextra # -g -fsanitize=address
MAKEFLAGS		:= --no-print-directory

# Includes
HDR_FILES :=	libft.h

# Files
SRC_FILES :=	ft_isalnum.c		\
				ft_isascii.c		\
				ft_isprint.c		\
				ft_memmove.c		\
				ft_strlcat.c		\
				ft_strlen.c			\
				ft_bzero.c			\
				ft_isalpha.c		\
				ft_isdigit.c		\
				ft_memcpy.c			\
				ft_memset.c			\
				ft_strlcpy.c		\
				ft_toupper.c		\
				ft_tolower.c		\
				ft_strchr.c			\
				ft_strrchr.c		\
				ft_strcmp.c			\
				ft_strncmp.c		\
				ft_memchr.c			\
				ft_memcmp.c			\
				ft_strnstr.c		\
				ft_err_atoi.c		\
				ft_calloc.c			\
				ft_strdup.c			\
				ft_substr.c			\
				ft_strjoin.c		\
				ft_strtrim.c		\
				ft_split.c			\
				ft_itoa.c			\
				ft_strmapi.c		\
				ft_striteri.c		\
				ft_putchar_fd.c		\
				ft_putstr_fd.c		\
				ft_putendl_fd.c		\
				ft_putnbr_fd.c		\
				ft_free_str_arr.c	\
				ft_strcpy.c			\
				ft_strcat.c			\

SRC				:= $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ				:= ${addprefix ${OBJ_DIR}/, ${SRC_FILES:.c=.o}}
HDR				:= $(addprefix $(HDR_DIR)/, $(HDR_FILES))

# Colours
GREEN			:= \033[32;1m
YELLOW			:= \033[33;1m
RED				:= \033[31;1m
BOLD			:= \033[1m
RESET			:= \033[0m

# Rules
all: ${NAME}

$(NAME): $(OBJ)
	@ printf "%b%s%b" "$(YELLOW)$(BOLD)" "Compiling ${NICKNAME}..." "$(RESET)"
	@ ar rc ${NAME} ${OBJ}
	@ printf "\t\t\t%b%s%b\n" "$(GREEN)$(BOLD)" "[OK]" "$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HDR)
	@ mkdir -p obj
	@ printf "%b%s%b" "$(YELLOW)" "Compiling $<..." "$(RESET)"
	@ gcc $(CFLAGS) -I $(HDR_DIR) -c $< -o $@
	@ printf "\t\t\t%b%s%b\n" "$(GREEN)$(BOLD)" "[OK]" "$(RESET)"

norm:
	@ norminette $(SRC) $(HDR)

clean:
	@ printf "%b%s%b\n" "$(RED)$(BOLD)" "Cleaning object files in $(NICKNAME)..." "$(RESET)"
	@ rm -rf $(OBJ_DIR)

fclean: clean
	@ printf "%b%s%b\n" "$(RED)$(BOLD)" "Cleaning executable in $(NICKNAME)..." "$(RESET)"
	@ rm -rf ${NAME}

re: fclean ${NAME}

.PHONY: all norm clean fclean re

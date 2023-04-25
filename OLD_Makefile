NAME = minishell
CC = gcc
FLAGS = -g -Wall -Werror -Wextra -fsanitize=address
SRC = main.c create_list.c ft_split.c ft_strdup.c ft_strlcpy.c ft_strlen.c ft_substr.c ft_memcpy.c ft_free_s.c ft_add_nodes.c \
		ft_free_list.c parse.c ft_strncmp.c ft_strtrim.c ft_strchr.c quote_count.c tokens.c
HEAD = minishell.h
OBJDIR = build
OBJ = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))

#DONT FORGET TO PAY ELECTRICITY AND ALSO TO REMOVE THE COMMAND LINE AT THE "all:" RULE

all: $(OBJDIR) $(NAME)
	./$(NAME)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: %.c $(HEAD)
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $@ -lreadline

# run: $(NAME)
# 	./$(NAME)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all
	
.PHONY: clean fclean re all

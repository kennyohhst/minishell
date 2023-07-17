libft := ../../lib/libft/libft.a

all: compile

compile:
	@touch input.txt
	@echo hello world > input.txt
	@gcc $(libft) *.c -Wall -Werror -Wextra -o pipes -g -fsanitize=address && ./pipes

clean:
	@rm -rf *txt pipes pipes.dSYM

re: clean all
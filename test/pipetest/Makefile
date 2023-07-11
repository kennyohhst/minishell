all: compile

compile:
	@touch input.txt
	@echo hello world > input.txt
	@gcc new_test.c fake_input_creation.c -Wall -Werror -Wextra -o pipes -g -fsanitize=address && ./pipes

clean:
	@rm -rf *txt pipes pipes.dSYM

re: clean all
all: compile

compile:
	@gcc new_test.c fake_input_creation.c -Wall -Werror -Wextra -o pipes -g -fsanitize=address && ./pipes

clean:
	@rm -rf output.txt pipes pipes.dSYM

re: clean all
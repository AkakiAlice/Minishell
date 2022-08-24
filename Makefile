# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/16 23:17:06 by alida-si          #+#    #+#              #
#    Updated: 2022/08/24 13:52:00 by alida-si         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

## COLORS ##

DEFAULT		=	\e[39m
GREEN		=	\e[92m
YELLOW		=	\e[93m
MAGENTA		=	\e[95m
CYAN		=	\e[96m

# **************************************************************************** #

NAME = minishell

# LIBRARY #

LIBFT = libft.a
LIBFT_DIR = ./libft/
HEADER = -I includes -I $(LIBFT_DIR)includes
LIB_FLAGS = -L $(LIBFT_DIR) -lft
READLINE_FLAG = -lreadline

# COMPILATION #

CC = gcc
CFLAGS = -Wall -Wextra -Werror

# DELETE #

RM = rm -rf

# DIRECTORIES #

SRC_DIR = ./src/

VPATH = $(SRC_DIR)\
		$(SRC_DIR)builtins\
		$(SRC_DIR)parser\
		$(SRC_DIR)quotes\
		$(SRC_DIR)system\
		$(SRC_DIR)utils\
		$(SRC_DIR)variable\
		$(SRC_DIR)command_table\
		$(SRC_DIR)expand\
		$(SRC_DIR)exec

# FILES #

FILES = main.c\
		get_prompt.c\
		tokenizer.c\
		env_lst.c\
		save_env.c\
		token_lst.c\
		lexer.c\
		str_withou_quotes.c\
		validate_quote.c\
		put_msg.c\
		remove_spaces_around_str.c\
		save_var.c\
		validate_var.c\
		var_utils.c\
		error.c\
		parser.c\
		exit_cmd.c\
		builtin.c\
		exec_cmd.c\
		get_path.c\
		free_minishell.c\
		init_minishell.c\
		cmd_table_lst.c\
		cmd_table_utils.c\
		create_cmd_table.c\
		check_cmd.c\
		syntax_error.c\
		remove_spaces_outside_quotes.c\
		split_cmd.c\
		skip_with_quotes.c\
		reserved_word.c\
		save_reserved_word.c\
		save_word_with_quotes.c\
		expand.c\
		exec_cmd_utils.c

# COMPILED_SOURCES #

OBJ_DIR = ./obj/
OBJS = $(addprefix $(OBJ_DIR), $(notdir $(FILES:.c=.o)))

# **************************************************************************** #

## RULES ##

$(OBJ_DIR)%.o: %.c
		@$(CC) $(CFLAGS) $(HEADER) -c $< -o $@

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
		@echo "\n$(CYAN)----------------------------------------"
		@echo "------------ MAKE MINISHELL ------------"
		@echo "----------------------------------------\n$(DEFAULT)"
		@$(CC) $(CFLAGS) $(OBJS) $(LIB_FLAGS) $(READLINE_FLAG) $(HEADER) -o $(NAME)

$(OBJS): | $(OBJ_DIR)

$(OBJ_DIR):
		@mkdir $(OBJ_DIR)

$(LIBFT):
		@make --no-print-directory -C $(LIBFT_DIR)

clean:
		@make clean --no-print-directory -C $(LIBFT_DIR)
		@$(RM) $(OBJ_DIR) $(TEST_OBJS) *.gc*

fclean: clean
		@make fclean --no-print-directory -C $(LIBFT_DIR)
		@$(RM) $(NAME) $(TEST_DIR)bin/ valgrind-out.txt
		@echo "\n$(MAGENTA)----------------------------------------"
		@echo "------------- CLEANING DONE ------------"
		@echo "----------------------------------------\n$(DEFAULT)"

re: fclean all

# CHECK MEMORY LEAK #

release: CFLAGS+=-g -fsanitize=address
release: fclean
release: $(NAME)

debug: CFLAGS+=-g
debug: fclean
debug: $(NAME)

valgrind: re
	@valgrind --suppressions=./readline.supp --leak-check=full --show-leak-kinds=all ./minishell

# NORMINETTE #
norm:
	norminette $(find -name '*.c' -not -path '*/tests/*')
	norminette $(find -name '*.h' -not -path '*/tests/*')

# **************************************************************************** #

## TESTS ##

TEST_DIR = ./tests/
TEST_FLAG = -lcriterion

# main file cannot be included in the tests
TEST_FILES = $(wildcard $(TEST_DIR)*.c)
TEST_FILES += $(wildcard ./src/builtins/*.c)
TEST_FILES += $(wildcard ./src/command_table/*.c)
TEST_FILES += $(wildcard ./src/exec/*.c)
TEST_FILES += $(wildcard ./src/parser/*.c)
TEST_FILES += $(wildcard ./src/quotes/*.c)
TEST_FILES += $(wildcard ./src/system/*.c)
TEST_FILES += $(wildcard ./src/utils/*.c)
TEST_FILES += $(wildcard ./src/variable/*.c)

TEST_OBJS = $(TEST_FILES:.c=.o)

test: CFLAGS+=-fsanitize=address
test:
	@mkdir -p $(TEST_DIR)bin/
	@gcc $(CFLAGS) $(TEST_FILES) $(HEADER) $(LIB_FLAGS) $(READLINE_FLAG) -o $(TEST_DIR)bin/test $(TEST_FLAG)


run_tests: fclean $(LIBFT) test
	$(TEST_DIR)bin/test

run_tests_v: fclean $(LIBFT) test
	$(TEST_DIR)bin/test --verbose

.PHONY: all clean fclean re release valgrind norm run_tests run_tests_v

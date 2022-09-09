# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/16 23:17:06 by alida-si          #+#    #+#              #
#    Updated: 2022/09/09 13:51:42 by alida-si         ###   ########.fr        #
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
		validate_var.c\
		var_utils.c\
		error.c\
		parser.c\
		builtin_exit.c\
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
		split_cmd.c\
		skip_with_quotes.c\
		reserved_word.c\
		save_reserved_word.c\
		save_word_with_quotes.c\
		open_redirection.c\
		expand.c\
		exec_cmd_utils.c\
		error_exit.c\
		heredoc.c\
		strcmp_eq.c\
		expand_utils.c\
		signal.c\
		clear_minishell.c\
		builtin_echo.c\
		builtin_unset.c\
		builtin_pwd.c\
		builtin_export.c\
		builtin_export_utils.c\
		builtin_env.c\
		builtin_cd.c\
		get_prompt_utils.c

# COMPILED_SOURCES #

OBJ_DIR = ./obj/
OBJS = $(addprefix $(OBJ_DIR), $(notdir $(FILES:.c=.o)))

# **************************************************************************** #

## RULES ##

$(OBJ_DIR)%.o: %.c
		@$(CC) $(CFLAGS) $(HEADER) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
		@make -C $(LIBFT_DIR)
		@echo "\n$(CYAN)----------------------------------------"
		@echo "------------ MAKE MINISHELL ------------"
		@echo "----------------------------------------\n$(DEFAULT)"
		@$(CC) $(CFLAGS) $(OBJS) $(LIB_FLAGS) $(READLINE_FLAG) $(HEADER) -o $(NAME)

$(OBJS): | $(OBJ_DIR)

$(OBJ_DIR):
		@mkdir $(OBJ_DIR)

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

.PHONY: all clean fclean re

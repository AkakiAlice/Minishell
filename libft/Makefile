# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/30 19:35:16 by alida-si          #+#    #+#              #
#    Updated: 2022/09/07 19:46:42 by alida-si         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

# COMPILATION #

CC = gcc
CFLAG = -Wall -Wextra -Werror
AR = ar -rcs
HEADER = -I includes

# DELETE #

RM = rm -f

# DIRECTORIES #

SRC_DIR = ./src/

VPATH = $(SRC_DIR)\
		$(SRC_DIR)free\
		$(SRC_DIR)gnl\
		$(SRC_DIR)is\
		$(SRC_DIR)lst\
		$(SRC_DIR)mem\
		$(SRC_DIR)printf\
		$(SRC_DIR)put\
		$(SRC_DIR)str\
		$(SRC_DIR)to

# FILES #

FILES = ft_matrix_free.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_strlen.c \
		ft_atoi.c \
		ft_bzero.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_memcpy.c \
		ft_memset.c \
		ft_memmove.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_strncmp.c \
		ft_strncmp_eq.c \
		ft_strnstr.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_calloc.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_strdup.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_itoa.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_strmapi.c \
		ft_striteri.c \
		ft_putnbr_fd.c \
		ft_split.c \
		conversions.c \
		ft_printf.c \
		itohex.c \
		utoa.c \
		ft_printf_utils.c \
		get_next_line.c \
		ft_strrncmp.c \
		ft_strcat.c \
		ft_split2.c \
		ft_lstnew.c \
		ft_lstadd_front.c \
		ft_lstsize.c \
		ft_lstlast.c \
		ft_lstadd_back.c \
		ft_lstdelone.c \
		ft_lstclear.c \
		ft_lstiter.c \
		ft_skip.c \
		ft_lstmap.c


# COMPILED_SOURCES #

OBJ_DIR = ./obj/
OBJS = $(addprefix $(OBJ_DIR), $(notdir $(FILES:.c=.o)))

# **************************************************************************** #

## RULES ##

$(OBJ_DIR)%.o: %.c
		@$(CC) $(CFLAGS) $(HEADER) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
		@$(AR) $(NAME) $(OBJS)

$(OBJS): | $(OBJ_DIR)

$(OBJ_DIR):
		@mkdir $(OBJ_DIR)

clean:
		@$(RM) $(OBJS)

fclean: clean
		@$(RM) $(NAME)
		@$(RM) -r $(OBJ_DIR)

re: fclean all

.PHONY: all clean fclean re

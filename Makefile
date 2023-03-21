# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/19 09:22:41 by ybenlafk          #+#    #+#              #
#    Updated: 2023/03/21 20:34:30 by ybenlafk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= minishell

HEADER= minishell.h

SRCS= tools/utils.c\
	src/lst_funs.c\
	src/parsing.c\
	tools/libft.c\
	tools/expanding_utils_1.c\
	tools/parsing_utils_1.c\
	tools/parsing_utils_2.c\
	tools/expanding_utils.c\
	tools/parsing_utils.c\
	redirections/all.c\
	redirections/heredoc.c\
	src/syntax.c\
	src/parser.c\
	src/expanding.c\
	src/minishell.c\

OBGJ= $(SRCS:.c=.o)
CC = cc
# CFLAGS = -Wall -Wextra -Werror -g
# CFLAGS = -g -fsanitize=address
R_L = "-L/Users/ybenlafk/.brew/opt/readline/lib"
R_I = "-I/Users/ybenlafk/.brew/opt/readline/include"
LDFLAGS = $(R_L) -lreadline
FRM = rm -rf

all: $(NAME)

$(NAME): $(OBGJ)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBGJ) -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS)  -c $< $(R_I) -o $@

clean:
	$(FRM) $(OBGJ) 

fclean: clean
	$(FRM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/18 15:28:07 by ybenlafk          #+#    #+#              #
#    Updated: 2023/03/18 17:22:33 by ybenlafk         ###   ########.fr        #
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
	redirections/in.c\
	redirections/out.c\
	redirections/append.c\
	redirections/heredoc.c\
	src/syntax.c\
	src/expanding.c\
	src/minishell.c\

OBGJ= $(SRCS:.c=.o)
CC = cc
# CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lreadline
FRM = rm -rf

all: $(NAME)

$(NAME): $(OBGJ)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBGJ) -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(FRM) $(OBGJ) 

fclean: clean
	$(FRM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
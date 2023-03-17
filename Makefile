# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/11 11:52:19 by ybenlafk          #+#    #+#              #
#    Updated: 2023/03/17 13:29:37 by ybenlafk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= minishell

HEADER= minishell.h

SRCS= utils/utils.c\
	src/lst_funs.c\
	src/parsing.c\
	utils/libft.c\
	utils/expanding_utils_1.c\
	utils/parsing_utils_1.c\
	utils/parsing_utils_2.c\
	utils/expanding_utils.c\
	utils/parsing_utils.c\
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
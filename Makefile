# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nouahidi <nouahidi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/19 09:22:41 by ybenlafk          #+#    #+#              #
#    Updated: 2023/04/20 01:56:25 by nouahidi         ###   ########.fr        #
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
	tools/split.c\
	redirections/all.c\
	redirections/heredoc.c\
	src/syntax.c\
	src/parser.c\
	src/expanding.c\
	src/command.c\
	src/execution.c\
	src/cd_command.c\
	src/pwd_command.c\
	src/echo_command.c\
	src/env_command.c\
	src/export_command.c\
	src/unset_command.c\
	src/minishell.c\
	src/exit_command.c\
	src/export_util.c\
	src/export_util2.c\
	src/export_util3.c\
	src/export_util1.c\
	src/cd_command_util.c\
	src/cd_command_util1.c\
	src/cd_command_util2.c\
	src/execution_util.c\
	src/execution_util1.c\
	src/lst_funs_util.c\
	redirections/all_util.c \

OBGJ= $(SRCS:.c=.o)
CC = gcc
CFLAGS =  -g3
R_L = "-L/Users/nouahidi/.brew/opt/readline/lib"
R_I = "-I/Users/nouahidi/.brew/opt/readline/include"
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

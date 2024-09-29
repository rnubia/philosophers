# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rnubia <rnubia@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/16 12:14:14 by rnubia            #+#    #+#              #
#    Updated: 2022/07/09 14:34:43 by rnubia           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo

HEADER		=	philo.h

SRCS		=	philo_main.c	philo_cycle.c\
				philo_init.c	philo_utils.c\
				philo_time.c

OBJ			=	$(SRCS:%.c=%.o)

CC			=	clang

CFLAGS		=	-Wall -Wextra -Werror -pthread
#CFLAGS		=	-Wall -Wextra -Werror -pthread -g -fsanitize=thread
#CFLAGS		=	-Wall -Wextra -Werror -pthread -g -fsanitize=address

RM			=	rm -f

.PHONY		:	all bonus clean fclean re

all			:	$(NAME)

$(NAME)		:	$(OBJ)
				$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o			:	%.c $(HEADER)
				$(CC) $(CFLAGS) -c $< -o $@

clean		:
				$(RM) $(OBJ) $(BOBJ)

fclean		:	clean
				$(RM) $(NAME) $(BNAME)

re			:	fclean all

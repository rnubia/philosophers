# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rnubia <rnubia@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/06 11:21:14 by rnubia            #+#    #+#              #
#    Updated: 2022/07/11 02:33:56 by rnubia           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo_bonus

HEADER		=	philo_bonus.h

SRCS		=	philo_main_bonus.c	philo_cycle_bonus.c\
				philo_init_bonus.c	philo_utils_bonus.c\
				philo_time_bonus.c

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

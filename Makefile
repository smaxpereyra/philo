# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: spereyra <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/05 12:57:20 by spereyra          #+#    #+#              #
#    Updated: 2024/07/06 21:25:48 by spereyra         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:=	philo
SRC		:=	main.c philo.c time.c ft_atoi.c setter.c getter.c error.c
OBJ		:=	$(SRC:.c=.o)
INCLUDE	:=	philo.h
CC		:=	gcc
CFLAGS	:=	-Wall -Werror -Wextra -lpthread# -fsanitize=address
RM		:=	rm -f

.PHONY	: all clean fclean re

all	: $(NAME)

$(NAME) : $(OBJ) $(INCLUDE) Makefile
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

%.o	: %.c $(INCLUDE)
	$(CC) $(CFLAGS) -c $< -o $@

clean	:
	$(RM) $(OBJ)

fclean	: clean
	$(RM) $(NAME)

re:	fclean all

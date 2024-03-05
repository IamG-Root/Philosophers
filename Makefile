# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: scastagn <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/29 11:33:17 by scastagn          #+#    #+#              #
#    Updated: 2023/03/29 11:33:19 by scastagn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = gcc
SRCS = main.c start.c end.c case_one.c utils.c simulation.c philo_actions.c
OBJS = $(SRCS:.c=.o)

.o:.c
	$(CC) -Wall -Wextra -Werror -c $< -o $@

all :		$(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re

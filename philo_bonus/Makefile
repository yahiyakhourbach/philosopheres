# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ykhourba <ykhourba@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/19 13:33:39 by ykhourba          #+#    #+#              #
#    Updated: 2023/04/06 18:28:28 by ykhourba         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
OBG = philo.o utils.o env_init.o manage_processes.o philo_utils.o itoa.o
HEADER = philo.h
NAME = philo_bonus

all : $(NAME)

%.o : %.c $(HEADER)
	$(CC) $(CFLAGS)  -c -o $@ $< 
$(NAME) : $(OBG)
	$(CC) $(CFLAGS)  $(OBG)   -o $(NAME)

clean :
	rm -rf $(OBG)
fclean : clean
	rm -rf $(NAME)

re: fclean all
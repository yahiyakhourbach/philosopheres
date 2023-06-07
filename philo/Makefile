# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ykhourba <ykhourba@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/19 13:33:39 by ykhourba          #+#    #+#              #
#    Updated: 2023/04/06 17:50:09 by ykhourba         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror 
OBG = philo.o utils.o env_init.o manage_threads.o philo_utils.o
HEADER = philo.h
NAME = philo

all : $(NAME)

%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) -c -o $@ $<
$(NAME) : $(OBG)
	$(CC) $(CFLAGS) $(OBG)  -o $(NAME)

clean :
	rm -rf $(OBG)
fclean : clean
	rm -rf philo

re: fclean all
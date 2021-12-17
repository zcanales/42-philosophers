# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/25 09:49:26 by zcanales          #+#    #+#              #
#    Updated: 2021/12/16 18:32:14 by zcanales         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS =	src/main.c\
		src/init.c\
		src/thread.c\
		src/get_time.c\
		src/actions.c\
		src/utils.c\

OBJS = $(SRCS:.c=.o)
OBJ_DIR = obj

MAKE = make
GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

INCLUDE = include/philo.h

CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread


all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -I$(INCLUDE) -pthread $^ -o $(NAME)
	@mv $(OBJS) $(OBJ_DIR)
	@echo "$(NAME): $(GREEN) $(NAME) was created$(RESET)"

$(OBJ_DIR):
	@mkdir $@

%.o: %.c $(OBJ_DIR) $(INCLUDE)
	@$(CC) $(CFLAGS) -pthread -I$(INCLUDE) -c $< -o $@

clean :
	@rm -rf obj/
	@echo "$(NAME): $(RED)object files were deleted$(RESET)"

fclean : clean
	@rm -rf $(NAME)
	@echo "$(NAME): $(RED)$(NAME) was deleted$(RESET)"

re: fclean all

.PHONY : re all fclean clean

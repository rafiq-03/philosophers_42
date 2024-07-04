# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/01 19:22:06 by rmarzouk          #+#    #+#              #
#    Updated: 2024/06/23 17:22:05 by rmarzouk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=philo

### FLAGS

CC=cc
CFLAGS=-Wall -Wextra -Werror
TH_FLAG=-pthread

UTILS_S=philo.c\
		ft_init.c\
		utils.c\
		ft_routine.c\
		ft_close.c

UTILS_O=$(UTILS_S:.c=.o)
all: $(NAME)

$(NAME): $(UTILS_O)
	$(CC) $(CFLAGS) $(TH_FLAG) $(UTILS_O) -o $(NAME)
	
#_________________________________________________________

%.o:%.c philo.h
	${CC} ${CFLAGS} -c $< -o $@

clean:
	@echo "Cleanin object files ..."
	@rm -f $(UTILS_O)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: clean

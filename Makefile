# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kmoutaou <kmoutaou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/25 02:40:09 by kmoutaou          #+#    #+#              #
#    Updated: 2022/08/11 11:10:44 by kmoutaou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo

BNAME		= 

CC			= cc

FLAGS		= -Wall -Wextra -Werror -pthread

SRCS		= philo.c tools/ft_atoi.c tools/initialization.c \
			  tools/handlers.c tools/monitoring.c tools/timing.c

OBJS		= $(SRCS:.c=.o)

BOBJS		= $(BSRCS:.c=.o)

HEADERS		= include/philo.h

all: 		$(NAME)

bonus:		$(BNAME)

$(NAME):	$(SRCS)
			$(CC) $(FLAGS) $(SRCS) -o $(NAME)

$(BNAME):	$(BSRCS)
			$(CC) $(FLAGS) $(BSRCS) -o $(BNAME)

clean:
			rm -f $(NAME) $(BNAME)

fclean: 	clean
			rm -f $(NAME) $(BNAME)

re: 		fclean all

.PHONY: 	all re clean fclean 

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/23 18:12:02 by tlemma            #+#    #+#              #
#    Updated: 2022/01/20 15:50:42 by tlemma           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc 
CFLAGS = -Wall -Werror -Wextra -pthread

RM = rm -rf

AR = ar rs

SDIR = src
SRCS = philo.c philo_routine.c death_routine.c parse_args.c philo_utils.c time_utils.c

ODIR = objs
OBJS = $(patsubst %.c, %.o, $(SRCS))

$(NAME): $(addprefix $(SDIR)/, $(SRCS))
	$(CC) $(CFLAGS) -c $^
	@mkdir -p $(ODIR)
	@mv $(OBJS) $(ODIR)
	$(CC) $(CFLAGS) $(addprefix $(ODIR)/, $(OBJS)) -o $(NAME)
	@echo $(NAME) created!\\n

all: $(NAME)

clean:
	$(RM) $(ODIR)
	@echo $(ODIR) removed!\\n

fclean: clean
	$(RM) $(NAME)
	@echo $(NAME) removed!\\n

re: fclean all
		
.PHONY: all clean fclean re bonus .c .o
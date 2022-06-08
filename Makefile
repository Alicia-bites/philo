# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/23 17:34:14 by amarchan          #+#    #+#              #
#    Updated: 2022/06/08 11:50:37 by amarchan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

NORMINETTE_BIN = norminette

NM_BIN = nm

SRCS =	src/main.c \
		src/parsing.c \
		src/start_diner.c \
		src/create_fork.c \
		src/philo_does.c \
		src/time.c \
		src/time_utils.c \
		src/wait.c \
		src/fork.c \
		src/end_game.c \
		src/clean.c \
		utils/ft_atoi.c \
		utils/ft_atoll.c \
		utils/ft_isspace.c \
		utils/ft_isdigit.c \
		utils/ft_rstrip.c \
		utils/ft_lstrip.c \
		utils/ft_memmove.c \
		utils/ft_memcpy.c \
		utils/isinteger.c \
		utils/ft_strip.c \
		utils/ft_strlen.c \
		utils/ft_bzero.c \

OBJS := ${SRCS:.c=.o}

CC = cc

CFLAGS = -g3 -pthread -Wall -Wextra -Werror

AR = ar rcs

RM = rm -rf

INC_DIR = headers

.c.o: $(SRCS)
	$(CC) $(CFLAGS) -c -I ${INC_DIR} $< -o ${<:.c=.o}

all: $(NAME) 

$(NAME): ${OBJS}
	gcc $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	${RM} ${OBJS}

fclean:
	make clean
	$(RM) $(NAME)
  
re:
	make fclean
	make all

norme:
	${NORMINETTE_BIN} ${SRCS}

sym:
	${NM_BIN} -Dgu $(NAME)

.PHONY: all clean fclean re norme sym
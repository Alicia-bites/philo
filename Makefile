# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/23 17:34:14 by amarchan          #+#    #+#              #
#    Updated: 2022/06/02 12:38:33 by amarchan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

NORMINETTE_BIN = norminette

NM_BIN = nm

SRCS =	src/main.c \
		src/parsing.c \
		src/start_simulation.c \
		src/create_fork.c \
		src/philo_does.c \
		src/is_fork_free.c \
		src/time.c \
		src/time_utils.c \
		src/wait.c \
		src/fork.c \
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

CC = clang

CFLAGS = -pthread -Wall -Wextra -Werror -fPIE -g3

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

fclean: clean
	${RM} ${NAME}
	

re: fclean all

norme:
	${NORMINETTE_BIN} ${SRCS}

sym:
	${NM_BIN} -Dgu $(NAME)

.PHONY: all clean fclean re norme sym
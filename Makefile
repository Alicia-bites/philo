# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/23 17:34:14 by amarchan          #+#    #+#              #
#    Updated: 2022/05/26 13:46:57 by amarchan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

NAME_FT_PRINTF = ft_printf.a

NORMINETTE_BIN = norminette

NM_BIN = nm

DIR_FT_PRINTF = ft_printf/

SRCS =	src/main.c \
		src/parsing.c \
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

OBJS := ${SRCS:.c=.o}

CC = gcc

CFLAGS = -g3 -Wall -Wextra -Werror

AR = ar rcs

RM = rm -rf

INC_DIR = headers
INC_FT_PRINTF = ft_printf

.c.o: $(SRCS)
	$(CC) $(CFLAGS) -c -I ${INC_DIR} $< -o ${<:.c=.o}

all: $(NAME_FT_PRINTF) $(NAME) 

$(NAME_FT_PRINTF):
	make -C $(DIR_FT_PRINTF)
	cp $(DIR_FT_PRINTF)ft_printf.a .	

$(NAME): ${OBJS}
	gcc $(CFLAGS) -o $(NAME) $(OBJS) $(NAME_FT_PRINTF)

clean:
	${RM} ${OBJS}
	make -C $(DIR_FT_PRINTF) clean

fclean: clean
	${RM} ${NAME} ${NAME_FT_PRINTF}
	${RM} $(DIR_FT_PRINTF)ft_printf.a
	

re: fclean all

norme:
	${NORMINETTE_BIN} ${SRCS}

sym:
	${NM_BIN} -Dgu $(NAME)

.PHONY: all clean fclean re norme sym
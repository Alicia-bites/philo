# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/13 14:02:33 by amarchan          #+#    #+#              #
#    Updated: 2022/05/19 14:56:18 by amarchan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/04 09:22:13 by amarchan          #+#    #+#              #
#    Updated: 2022/04/12 18:53:28 by amarchan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philosophers

NAME_FT_PRINTF = ft_printf.a

NORMINETTE_BIN = norminette

NM_BIN = nm

DIR_FT_PRINTF = ft_printf/

SRCS =	src/main.c \

OBJS := ${SRCS:.c=.o}

CC = gcc

CFLAGS = -g3 -Wall -Wextra -Werror

AR = ar rcs

RM = rm -rf

INC_DIR = headers
INC_FT_PRINTF = ft_printf

.c.o: $(SRCS)
	$(CC) $(CFLAGS) -c -I ${INC_DIR} -I ${INC_LIBFT} $< -o ${<:.c=.o} $(CFLAGS_MLX)

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
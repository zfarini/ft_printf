SRC		= ft_printf.c ft_printf_width.c ft_printf_numbers.c ft_printf_read.c ft_printf_utils.c
SRCS	= $(addprefix src/, ${SRC})
BSRC 	= ${SRC:.c=_bonus.c}
BSRCS	= $(addprefix bsrc/, ${BSRC})
OBJS	= ${SRCS:.c=.o}
BOBJS	= ${BSRCS:.c=.o}
LIBFT	= libft
NAME    = libftprintf.a
CC		= cc
CFLAGS  = -Wall -Wextra -Werror -fsanitize=address -fsanitize=undefined
AR		= ar rcs
RM		= rm -f


all: ${NAME}

${NAME}: ${OBJS} comp_libft
	${AR} ${NAME} ${OBJS}

bonus: ${BOBJS} comp_libft
	${AR} ${NAME} ${BOBJS}

comp_libft:
	make -C ${LIBFT}
	cp ${LIBFT}/libft.a ${NAME}

clean:
	make clean -C ${LIBFT}
	${RM} ${OBJS} ${BOBJS} tester.o

fclean: clean
	${RM} ${LIBFT}/libft.a
	${RM} ${NAME}

test: tester.o ${NAME}
	${CC} ${CFLAGS} ${NAME} tester.c -o test

re: fclean all

.PHONY: all bonus test comp_libft clean fclean re
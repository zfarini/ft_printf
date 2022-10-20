SRCS	=	ft_printf.c ft_printf_width.c ft_printf_numbers.c ft_printf_read.c ft_printf_utils.c tester.c
OBJS	= ${SRCS:.c=.o}
LIBFT	= libft
NAME    = libftprintf.a
CC		= cc
CFLAGS  = -Wall -Wextra -fsanitize=address -fsanitize=undefined
AR		= ar rcs
RM		= rm -f

all: ${NAME}

${NAME}: ${OBJS}
	make -C ${LIBFT}
	mv ${LIBFT}/libft.a ${NAME}
	${AR} ${NAME} ${OBJS}
	${CC} ${CFLAGS} tester.o ${NAME}

clean:
	make clean -C ${LIBFT}
	${RM} ${OBJS}

fclean: clean
	${RM} ${LIBFT}/libft.a
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
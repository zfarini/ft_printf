SRC		= ft_printf.c ft_printf_width.c ft_printf_numbers.c ft_printf_read.c ft_printf_utils.c ft_printf_utils2.c
SRCS	= $(addprefix src/, ${SRC})
BSRC 	= ${SRC:.c=_bonus.c}
BSRCS	= $(addprefix bsrc/, ${BSRC})
OBJS	= ${SRCS:.c=.o}
BOBJS	= ${BSRCS:.c=.o}
DEPS	= ${OBJS:.o=.d}
BDEPS	= ${BOBJS:.o=.d}
NAME    = libftprintf.a
CC		= cc
CPPFLAGS = -MMD 
CFLAGS  = -Wall -Wextra# -Werror -fsanitize=address -fsanitize=undefined
AR		= ar rcs
RM		= rm -f

all: ${NAME}

${NAME}: ${OBJS} 
	${AR} ${NAME} ${OBJS}

bonus: ${BOBJS}
	${AR} ${NAME} ${BOBJS}

clean:
	${RM} ${OBJS} ${DEPS} ${BOBJS} ${BDEPS}

fclean: clean
	${RM} ${NAME} test

test: tester.c ${NAME}
	${CC} tester.c ${CFLAGS} ${NAME} -o test

re: fclean all

-include ${DEPS} ${BDEPS}

.PHONY: all bonus clean fclean re
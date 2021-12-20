NAME = minishell

LIBFT = libft/libft.a

SRCS = main.c\
		srcs/builtins/ft_cd.c\
		srcs/builtins/ft_convert.c\
		srcs/builtins/ft_copy_env.c\
		srcs/builtins/ft_echo.c\
		srcs/builtins/ft_env.c\
		srcs/builtins/ft_exit.c\
		srcs/builtins/ft_export.c\
		srcs/builtins/ft_pwd.c\
		srcs/builtins/ft_search_value.c\
		srcs/builtins/ft_sort_export.c\
		srcs/builtins/ft_unset.c\
		srcs/test_parsing/exec_test_parsing.c\
		srcs/exec/exec.c
		
CC = clang

OBJS = ${SRCS:.c=.o}

CFLAGS = -g3

all : $(NAME)

.c.o :
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o} 

$(NAME): ${OBJS}
		make -C libft
		${CC} -o ${NAME} ${OBJS} ${LIBFT} -lreadline

clean :
		rm -rf ${OBJS}

fclean: clean
		rm -rf ${NAME}

re:		fclean all

.PHONY: all clean fclean re

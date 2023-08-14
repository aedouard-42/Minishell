# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/02 14:32:03 by lnelson           #+#    #+#              #
#    Updated: 2022/01/11 16:40:29 by lnelson          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

SRCS_DIR	= srcs/

OBJS_DIR	= objs/

INCLS_DIR	= includes/

LIBS_DIR	= libft/

CFLAGS		= -Wall -Wextra -Werror -I ${INCLS_DIR}

FLAGS		= -L ${LIBS_DIR} -lft -lreadline

CC			= gcc

SRCS		=	main.c\
				main_utils.c\
				builtins/ft_echo.c\
				builtins/ft_exit.c\
				builtins/ft_pwd.c\
				builtins/ft_env.c\
				builtins/ft_export.c\
				builtins/ft_cd.c\
				builtins/ft_unset.c\
				builtins/export_utils.c\
				exec/exec.c\
				exec/get_path.c\
				exec/redirections.c\
				exec/exec_builtins.c\
				exec/pipeflow.c\
				exec/acces.c\
				parsing/expand/expand_dollar_utils.c\
				parsing/expand/expand_dollar.c\
				parsing/expand/expand_quotes.c\
				parsing/expand/expand_words.c\
				parsing/ft_lst/ft_cmd_lst_utils.c\
				parsing/ft_lst/ft_cmd_lst.c\
				parsing/ft_lst/ft_redir_lst.c\
				parsing/ft_lst/ft_tok_lst_utils.c\
				parsing/ft_lst/ft_tok_lst.c\
				parsing/parsing/check_syntax.c\
				parsing/parsing/get_lists.c\
				parsing/parsing/parse_redirs_dollar.c\
				parsing/parsing/parse_redirs_utils.c\
				parsing/parsing/parse_redirs.c\
				parsing/parsing/parse_tokens.c\
				parsing/parsing/parsing_utils.c\
				parsing/parsing/spec_tokens_utils.c\
				parsing/parsing/spec_tokens.c\
				signals/signal.c\
				signals/handlers.c\
				utils/ft_convert.c\
				utils/utils.c\
				utils/ft_copy_env.c\
				utils/ft_search_value.c\
				utils/utils_2.c\
				utils/ft_free_lists.c\

OBJS		= ${SRCS:.c=.o}

OBJS		:= ${addprefix ${OBJS_DIR}, ${OBJS}}

${OBJS_DIR}%.o: ${SRCS_DIR}%.c
			${CC} ${CFLAGS} -c $< -o $@

all:		${NAME}



${NAME}:	${OBJS}
			make -C ${LIBS_DIR}
			${CC} -o $@ ${OBJS} ${FLAGS} 


sanitize:	${OBJS}
			make -C ${LIBS_DIR}
			${CC} -o $@ ${OBJS} ${FLAGS} -g3 -fsanitize=address	

clean:
			make clean -C ${LIBS_DIR}
			${RM} ${OBJS}
			
fclean:		clean
			make fclean -C ${LIBS_DIR}
			${RM} ${NAME} sanitize

re:			fclean all

RM			= rm -f

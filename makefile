# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: disilva <disilva@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/11 22:46:03 by abekri            #+#    #+#              #
#    Updated: 2024/08/20 23:59:32 by disilva          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIBFT = libft/libft.a
INCLUDE = -I include -I libft -g

SRCS = src/main.c \
       src/signals.c \
       src/terminal.c \
       src/terminal_part2.c \
       src/parser/lexer.c \
       src/parser/check_syntax.c \
       src/parser/command_handler.c \
       src/parser/command_handler_part2.c \
       src/parser/tokenization.c \
       src/parser/tokenization_part2.c \
       src/parser/tokenization_part3.c \
       src/parser/expansion.c \
       src/parser/expansion_part2.c \
       src/parser/expansion_part3.c \
       src/parser/expansion_part4.c \
       src/parser/expansion_part5.c \
       src/parser/redirections.c \
       src/parser/redirections_part2.c \
       src/start_info/adjust_shell_lvl.c\
       src/start_info/adjust_shell_lvl_part2.c\
       src/start_info/adjust_shell_lvl_part3.c\
       src/start_info/format_term.c \
       src/start_info/format_term_part2.c \
       src/start_info/start_minishell.c \
       src/start_info/start_minishell_part2.c \
       src/start_info/start_minishell_part3.c \
       src/execution/execution_command.c \
       src/execution/multiple_command.c \
       src/execution/multiple_command_part2.c \
       src/execution/single_command.c \
       src/execution/single_commands_part2.c \
       src/execution/single_commands_part3.c \
       src/execution/single_commands_part4.c \
       src/execution/single_commands_part5.c \
       src/execution/builtins/cd.c \
       src/execution/builtins/cd_part2.c \
       src/execution/builtins/cd_part3.c\
       src/execution/builtins/cd_part4.c \
       src/execution/builtins/echo.c \
       src/execution/builtins/echo_part2.c \
       src/execution/builtins/env.c \
       src/execution/builtins/exit.c \
       src/execution/builtins/export.c \
       src/execution/builtins/export_part2.c \
       src/execution/builtins/export_part3.c \
       src/execution/builtins/export_part4.c \
       src/execution/builtins/pwd.c \
       src/execution/builtins/unset.c \
       src/execution/builtins/unset_part2.c \
       src/history.c \
       src/debug/minishell_printf_utils.c \
      src/execution/builtins/export_part5.c \
      src/execution/builtins/export_part6.c 

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(INCLUDE) -lreadline

$(LIBFT):
	make -C libft

$(OBJS): %.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make -C libft clean
	rm -f $(OBJS)

fclean: clean
	make -C libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

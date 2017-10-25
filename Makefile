# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cnovo-ri <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/15 13:14:57 by cnovo-ri          #+#    #+#              #
#    Updated: 2017/10/25 05:59:54 by cnovo-ri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=ft_ls

SRC=directory.c check_opts.c options.c options_2.c options_3.c options_4.c \
	tools.c refactoring.c rights.c args_and_files.c

LIB=./libft/libft.a

OBJ=$(SRC:.c=.o)

FLAGS=-Wall -Wextra -Werror

CC=cc

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft
	@$(CC) $(FLAGS) -c $(SRC) -I . -I ./libft
	@$(CC) $(FLAGS) $(OBJ) -o $(NAME) -I./  -L ./libft -lft
	@echo "\033[1m\033[32m[ ✔ ]Compiled :\033[0m $(NAME) ࿇"

clean:
	@rm -f $(OBJ)
	@make clean -C ./libft
	@echo "\033[1m\033[32m[ ✔ ]Deleted :\033[0m $(OBJ) ࿇"

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C ./libft
	@echo "\033[1m\033[32m[ ✔ ]Deleted :\033[0m $(NAME) ࿇"

re: fclean all

.PHONY: all clean fclean re

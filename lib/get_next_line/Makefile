# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dan <dan@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/02 10:40:29 by dsylvain          #+#    #+#              #
#    Updated: 2024/01/17 16:18:28 by dan              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = get_next_line.a

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRC =	get_next_line.c \
		get_next_line_utils.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs	$(NAME)	$(OBJ)
	@printf "%-80s\033[0;32mcompiled\033[0m\n" $(NAME)

%.o: %.c
	@gcc $(CFLAGS) -c $< -o $@

clean:
	@rm	-f	$(OBJ) $(OBJ_BONUS)

fclean: clean
	@rm	-f	$(NAME) 

re:	fclean	all


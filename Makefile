# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dan <dan@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/06 05:50:42 by dsylvain          #+#    #+#              #
#    Updated: 2024/01/24 09:09:01 by dan              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc

RLFLAGS = -lreadline -lhistory -I/usr/include/readline

CFLAGS = -g $(RLFLAGS)
# -Wall -Wextra -Werror

# Directories
LIBFT_DIR = lib/libft
FT_PRINTF_DIR = lib/ft_printf
GET_NEXT_LINE_DIR = lib/get_next_line

# lib paths
LIBFT = $(LIBFT_DIR)/libft.a
FT_PRINTF = $(FT_PRINTF_DIR)/libftprintf.a
GET_NEXT_LINE = $(GET_NEXT_LINE_DIR)/get_next_line.a

# lib flags
LIBS = -L$(LIBFT_DIR) -lft -L$(FT_PRINTF_DIR) -lftprintf -L$(GET_NEXT_LINE_DIR) -l:get_next_line.a

# Source files
SRC =	src/main.c \
		src/utils.c \
		src/handle_signals.c \
		src/exec_env.c \
		src/exec_pwd.c \
		src/exec_cd.c \
		src/exec_echo.c \
		src/exec_unset.c \
		src/exec_export.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(FT_PRINTF) $(GET_NEXT_LINE)
	@$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(LIBS)
	@echo "\033[0;32mCompilation successful\033[0m"
$(LIBFT):
	@make -s -C $(LIBFT_DIR)

$(FT_PRINTF):
	@make -s -C $(FT_PRINTF_DIR)

$(GET_NEXT_LINE):
	@make -s -C $(GET_NEXT_LINE_DIR)

%.o: %.c
	@printf "%-80s" $<
	@{ $(CC) $(CFLAGS) -I$(LIBFT_DIR) -I/usr/include -O3 -c $< -o $@; } 2>&1 || \
		(echo "\033[0;31mCompilation of $< failed\033[0m"; exit 1)
	@echo "\033[0;32mcompiled\033[0m"

clean:
	@rm	-f	$(OBJ) $(OBJ_BONUS)
	@make -s -C $(LIBFT_DIR) clean 
	@make -s -C $(FT_PRINTF_DIR) clean 
	@make -s -C $(GET_NEXT_LINE_DIR) clean 

fclean: clean
	@rm	-f	$(NAME) $(NAME_BONUS)
	@make -s -C $(LIBFT_DIR) fclean
	@make -s -C $(FT_PRINTF_DIR) fclean 
	@make -s -C $(GET_NEXT_LINE_DIR) fclean 

re:	fclean	all	

.PHONY: all clean fclean re

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seblin <seblin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/06 05:50:42 by dsylvain          #+#    #+#              #
#    Updated: 2024/02/06 17:28:31 by seblin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc

RLFLAGS = -lreadline -lhistory -I/usr/include/readline

CFLAGS = -g $(RLFLAGS) -Iincludes/parsing -Iincludes 
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
		src/builtins/exec_env.c \
		src/builtins/exec_pwd.c \
		src/builtins/exec_cd.c \
		src/builtins/exec_echo.c \
		src/builtins/exec_unset.c \
		src/builtins/exec_export.c \
		src/parsing/parsing_pipex/parsing_build.c \
		src/parsing/parsing_pipex/parsing_invrt.c \
		src/parsing/parsing_pipex/parsing_path.c \
		src/parsing/parsing_pipex/parsing_qute.c \
		src/parsing/parsing_pipex/parsing_spce.c \
		src/parsing/parsing_pipex/parsing_utils.c \
		src/parsing/parsing_minishell/parsing.c \
		src/parsing/parsing_minishell/parsing_qute.c \
		src/parsing/parsing_minishell/parsing_operator.c \
		src/parsing/parsing_minishell/parsing_utils.c \
		src/parsing/parsing_minishell/parsing_test.c \
		src/pipex/pipex.c \
		src/pipex/setup.c \
		
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
	@{ $(CC) $(CFLAGS) -I$(LIBFT_DIR) -I$(LIBFT_DIR) -I$(FT_PRINTF_DIR) -I/usr/include -O3 -c $< -o $@; } 2>&1 || \
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

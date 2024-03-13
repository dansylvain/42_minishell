# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dan <dan@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: Invalid date        by                   #+#    #+#              #
#    Updated: 2024/03/13 08:53:59 by dan              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell

CC = gcc

RLFLAGS = -lreadline -lhistory -I/usr/include/readline

CFLAGS = -g -Iincludes -Iincludes/main -Iincludes/parsing/parsing \
-Iincludes/parsing/create_tree \
-Iincludes/parsing/leaf_tree -Iincludes/pipex \
-Iincludes/exec_files -Iincludes/wildcard -Iincludes/builtins \
-Iincludes/post_parsing \
-Wall -Wextra -Werror \

# Directories
LIBFT_DIR = lib/libft
FT_PRINTF_DIR = lib/ft_printf

# lib paths
LIBFT = $(LIBFT_DIR)/libft.a
FT_PRINTF = $(FT_PRINTF_DIR)/libftprintf.a

# lib flags
LIBS = -L$(LIBFT_DIR) -lft -L$(FT_PRINTF_DIR) -lftprintf

# Source files
SRC =	test.c \
		src/main/main.c \
		src/main/utils.c \
		src/main/utils_2.c \
		src/main/utils_3.c \
		src/main/handle_signals.c \
		lib/gnl/get_next_line.c \
		lib/gnl/get_next_line_utils.c \
		src/builtins/exec_env.c \
		src/builtins/exec_pwd.c \
		src/builtins/exec_cd.c \
		src/builtins/exec_echo.c \
		src/builtins/exec_unset.c \
		src/builtins/exec_export.c \
		src/builtins/exec_export_utils.c \
		src/builtins/exec_export_utils_2.c \
		src/builtins/exec_exit.c \
		src/parsing/parsing/parsing.c \
		src/parsing/parsing/free_tree.c \
		src/parsing/parsing/utils.c \
		src/parsing/parsing/utils2.c \
		src/parsing/create_tree/expansion.c \
		src/parsing/create_tree/operator.c \
		src/parsing/create_tree/quote.c \
		src/parsing/create_tree/space.c \
		src/parsing/create_tree/token_child.c \
		src/parsing/leaf_tree/leaf.c \
		src/parsing/leaf_tree/dollar_expansion.c \
		src/post_parsing/create_command_tab_allocation.c \
		src/pipex/pipe_fwrd.c \
		src/pipex/path.c \
		src/pipex/pipex.c \
		src/pipex/utils.c \
		src/pipex/redir.c \
		src/pipex/fdio.c \
		src/pipex/here_doc.c \
		src/pipex/exit.c \
		src/post_parsing/create_command_tab_utils.c \
		src/post_parsing/exec_pipex.c \
		src/post_parsing/launch_command_tab.c \
		src/post_parsing/create_command_tab.c \
		src/wildcard/wildcard_expansion.c \
		src/wildcard/wildcard_expansion_2.c \
		src/post_parsing/fill_command_tab.c \
		src/post_parsing/fill_command_tab_utils.c \
		
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(FT_PRINTF)
	@$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(RLFLAGS) $(LIBS)
	@echo "\033[0;32mCompilation successful\033[0m"
$(LIBFT):
	@make -s -C $(LIBFT_DIR)

$(FT_PRINTF):
	@make -s -C $(FT_PRINTF_DIR)

%.o: %.c
	@printf "%-80s" $<
	@{ $(CC) $(CFLAGS) -I$(LIBFT_DIR) -I$(FT_PRINTF_DIR) -I/usr/include -O3 -c $< -o $@; } 2>&1 || \
		(echo "\033[0;31mCompilation of $< failed\033[0m"; exit 1)
	@echo "\033[0;32mcompiled\033[0m"

clean:
	@rm	-f	$(OBJ) $(OBJ_BONUS)
	@make -s -C $(LIBFT_DIR) clean 
	@make -s -C $(FT_PRINTF_DIR) clean 

fclean: clean
	@rm	-f	$(NAME) $(NAME_BONUS)
	@make -s -C $(LIBFT_DIR) fclean
	@make -s -C $(FT_PRINTF_DIR) fclean 

re:	fclean	all	

.PHONY: all clean fclean re

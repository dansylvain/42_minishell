# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dsylvain <dsylvain@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: Invalid date        by                   #+#    #+#              #
#    Updated: 2024/03/19 14:12:48 by dsylvain         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME_BONUS = minishell_bonus
NAME = minishell

CC = cc

RLFLAGS = -lreadline -lhistory -I/usr/include/readline

CFLAGS = -Iincludes -Iincludes/main -Iincludes/parsing/parsing \
-Iincludes/parsing/create_tree \
-Iincludes/parsing/leaf_tree -Iincludes/pipex \
-Iincludes/exec_files -Iincludes/wildcard -Iincludes/builtins \
-Iincludes/post_parsing \

CFLAGS_BONUS = 	-Ibonus/includes \
				-Ibonus/includes/main \
				-Ibonus/includes/parsing/parsing \
				-Ibonus/includes/parsing/create_tree \
				-Ibonus/includes/parsing/leaf_tree \
				-Ibonus/includes/pipex \
				-Ibonus/includes/exec_files \
				-Ibonus/includes/wildcard \
				-Ibonus/includes/builtins \
				-Ibonus/includes/post_parsing \
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
SRC =		src/main/main.c \
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
			src/post_parsing/fill_command_tab.c \
			src/post_parsing/fill_command_tab_utils.c \

SRC_BONUS =	bonus/src/main/main.c \
			bonus/src/main/utils.c \
			bonus/src/main/utils_2.c \
			bonus/src/main/utils_3.c \
			bonus/src/main/handle_signals.c \
			bonus/lib/gnl/get_next_line.c \
			bonus/lib/gnl/get_next_line_utils.c \
			bonus/src/builtins/exec_env.c \
			bonus/src/builtins/exec_pwd.c \
			bonus/src/builtins/exec_cd.c \
			bonus/src/builtins/exec_echo.c \
			bonus/src/builtins/exec_unset.c \
			bonus/src/builtins/exec_export.c \
			bonus/src/builtins/exec_export_utils.c \
			bonus/src/builtins/exec_export_utils_2.c \
			bonus/src/builtins/exec_exit.c \
			bonus/src/parsing/parsing/parsing.c \
			bonus/src/parsing/parsing/free_tree.c \
			bonus/src/parsing/parsing/utils.c \
			bonus/src/parsing/parsing/utils2.c \
			bonus/src/parsing/create_tree/expansion.c \
			bonus/src/parsing/create_tree/operator.c \
			bonus/src/parsing/create_tree/quote.c \
			bonus/src/parsing/create_tree/space.c \
			bonus/src/parsing/create_tree/token_child.c \
			bonus/src/parsing/leaf_tree/leaf.c \
			bonus/src/parsing/leaf_tree/dollar_expansion.c \
			bonus/src/post_parsing/create_command_tab_allocation.c \
			bonus/src/pipex/pipe_fwrd.c \
			bonus/src/pipex/path.c \
			bonus/src/pipex/pipex.c \
			bonus/src/pipex/utils.c \
			bonus/src/pipex/redir.c \
			bonus/src/pipex/fdio.c \
			bonus/src/pipex/here_doc.c \
			bonus/src/pipex/exit.c \
			bonus/src/post_parsing/create_command_tab_utils.c \
			bonus/src/post_parsing/exec_pipex.c \
			bonus/src/post_parsing/launch_command_tab.c \
			bonus/src/post_parsing/create_command_tab.c \
			bonus/src/wildcard/wildcard_expansion.c \
			bonus/src/wildcard/wildcard_expansion_2.c \
			bonus/src/post_parsing/fill_command_tab.c \
			bonus/src/post_parsing/fill_command_tab_utils.c \
			bonus/src/parsing/parsing/free_utils.c \
			bonus/src/parsing/create_tree/error_policy_and_fwrd.c \
			bonus/src/parsing/create_tree/parenthesis.c \
			bonus/src/parsing/create_tree/search_par.c \
			bonus/src/parsing/create_tree/fill_child_par.c \
			bonus/src/parsing/leaf_tree/leaf_par.c \
			bonus/src/parsing/leaf_tree/leaf_par_raw.c \
			bonus/src/post_parsing/post_parsing_utils.c \

		
OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)

all: $(NAME)

bonus: $(NAME_BONUS)

$(NAME): $(OBJ) $(LIBFT) $(FT_PRINTF)
	@$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(RLFLAGS) $(LIBS)
	@echo "\033[0;32mCompilation successful\033[0m"

$(NAME_BONUS): $(OBJ_BONUS) $(LIBFT) $(FT_PRINTF)
	@$(CC) -o $(NAME_BONUS) $(OBJ_BONUS) $(CFLAGS_BONUS) $(RLFLAGS) $(LIBS)
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
	
bonus/%.o: bonus/%.c
	@printf "%-80s" $<
	@{ $(CC) $(CFLAGS_BONUS) -I$(LIBFT_DIR) -I$(FT_PRINTF_DIR) -I/usr/include -O3 -c $< -o $@; } 2>&1 || \
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

rebonus: fclean bonus

.PHONY: all clean fclean re

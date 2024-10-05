# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tcohen <tcohen@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/02 02:26:37 by theog             #+#    #+#              #
#    Updated: 2024/10/05 14:16:19 by tcohen           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nom de l'exécutable
NAME = minitest

# Compilateur et options
CC = gcc
CFLAGS = -Wall -Wextra -Werror -fPIC -g3 # Added -fPIC for Position Independent Code
LDFLAGS = -lreadline -fPIE  # Added -fPIE for Position Independent Executable

# Dossiers
SRC_EXEC_DIR = ./exec
SRC_PARSING_DIR = ./parsing
LIBFT_DIR = ./libft
OBJ_EXEC_DIR = ./exec_obj
OBJ_PARSING_DIR = ./parsing_obj

# Fichiers sources pour exec et parsing
EXEC_FILES = ft_all.c ft_check.c ft_child.c ft_exec_one.c ft_heredoc.c \
             ft_make_exec.c ft_path.c ft_pipe_lst.c ft_secure.c \
             ft_set.c ft_while_cmd.c ft_token_to_exec.c
PARSING_FILES = TO_BIN_main_test.c TO_BIN_print_functions.c ft_join_all.c \
                garbage_collector.c helpers.c make_token_and_append.c \
                parse_quotes.c parsing_main.c replace_vars.c \
                split_array_tokens.c

# Fichiers objets (dans les dossiers correspondants)
OBJ_EXEC = $(addprefix $(OBJ_EXEC_DIR)/, $(EXEC_FILES:.c=.o))
OBJ_PARSING = $(addprefix $(OBJ_PARSING_DIR)/, $(PARSING_FILES:.c=.o))

# Bibliothèque libft
LIBFT = $(LIBFT_DIR)/libft.a

# Inclusions
INCLUDES = -I./ -I$(SRC_EXEC_DIR) -I$(SRC_PARSING_DIR) -I$(LIBFT_DIR)

# Règles
all: $(NAME)

# Compilation de l'exécutable
$(NAME): $(OBJ_EXEC) $(OBJ_PARSING) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ_EXEC) $(OBJ_PARSING) $(LIBFT) $(LDFLAGS) -o $(NAME)

# Compilation des fichiers objets dans exec
$(OBJ_EXEC_DIR)/%.o: $(SRC_EXEC_DIR)/%.c
	@mkdir -p $(OBJ_EXEC_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Compilation des fichiers objets dans parsing
$(OBJ_PARSING_DIR)/%.o: $(SRC_PARSING_DIR)/%.c
	@mkdir -p $(OBJ_PARSING_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Compilation de la libft
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# Nettoyage des objets et de l'exécutable
clean:
	rm -rf $(OBJ_EXEC_DIR) $(OBJ_PARSING_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

# Rebuild complet
re: fclean all

.PHONY: all clean fclean re


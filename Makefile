# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aquincho <aquincho@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/13 09:46:38 by aquincho          #+#    #+#              #
#    Updated: 2023/03/02 11:17:59 by aquincho         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub

CC			= gcc
CFLAGS		= -Wall -Werror -Wextra -g
RM			= rm -f
AR			= ar rcs

INC_DIR 	= ./include
INC_FLAGS = -I${INC_DIR} -I${LIBFT_INC_DIR} -I$(MLX_DIR)

LIBFT_DIR 	= ./libft
LIBFT_INC_DIR = $(LIBFT_DIR)/includes
MAKE_LIBFT 	= make -C ${LIBFT_DIR}
LIBFT 		= ${MAKE_LIBFT}
LIBFT_FLAGS = -L${LIBFT_DIR} -lft


MLX_DIR 		= mlx
MAKE_MLX	 	= make -C ${MLX_DIR}
MLX				= $(MAKE_MLX)
MLX_FLAGS		= -L$(MLX_DIR) -lmlx -lm #-framework OpenGL -framework AppKit

LIBS_FLAGS		= $(LIBFT_FLAGS) $(MLX_FLAGS)

SRC_DIR		= ./src/

MAIN_FILES = main.c init.c free.c error.c
MAIN_DIR=./
MAIN=$(addprefix ${MAIN_DIR}, ${MAIN_FILES})

PARSER_FILES= parser.c parser_utils.c
PARSER_DIR=./parser/
PARSER=$(addprefix ${PARSER_DIR}, ${PARSER_FILES})

SRC_FILES= $(MAIN) $(PARSER)

OBJ_DIR=./obj/
OBJ_FILES=${SRC_FILES:%.c=${OBJ_DIR}%.o}

all: $(NAME)

${NAME}: ${OBJ_FILES}
	$(MAKE_LIBFT)
	$(MAKE_MLX)
	${CC} ${CFLAGS} ${INC_FLAGS} ${OBJ_FILES} ${LIBS_FLAGS} -o ${NAME}

${OBJ_FILES}: ${OBJ_DIR}%.o : $(SRC_DIR)%.c
	mkdir -p $(@D)
	${CC} ${CFLAGS} ${INC_FLAGS} -c $^ -o $@

clean:
	${RM} -r ${OBJ_DIR}
	${MAKE_LIBFT} clean
	$(MAKE_MLX) clean
	@echo "\033[33;32m=== so_long object files deleted \t\t\t\tDONE\e[0m"

fclean:	clean
	$(RM) $(NAME)
	${MAKE_LIBFT} fclean
	@echo "\033[33;32m=== so_long bin file deleted \t\t\tDONE\e[0m"

re: fclean all

.PHONY: clean fclean re all

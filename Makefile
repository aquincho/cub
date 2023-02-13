# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aquincho <aquincho@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/13 09:46:38 by aquincho          #+#    #+#              #
#    Updated: 2023/02/13 11:09:30 by aquincho         ###   ########.fr        #
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
LIBFT_FLAGS = -L${LIBFT_PATH} -lft


MLX_DIR 		= mlx/
MAKE_MLX	 	= make -C ${MLX_DIR}
MLX				= $(MAKE_MLX)
MLX_FLAGS		= -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

LIBS_FLAGS		= $(LIBFT_FLAG) $(MLX_FLAGS)

SRC_DIR		= ./src/

MAIN_FILES = main.c init.c free.c error.c
MAIN_DIR=./
MAIN=$(addprefix ${MAIN_DIR}, ${MAIN_FILES})

PARSER_FILES= parser.c
PARSER_DIR=./parser/
PARSER=$(addprefix ${PARSER_DIR}, ${PARSER_FILES})

SRC_FILES= $(MAIN) $(PARSER)

OBJ_DIR=./obj/
OBJ_FILES=${SRC_FILES:%.c=${OBJ_DIR}%.o}

${OBJ_FILES}: ${OBJ_DIR}%.o : $(SRC_DIR)%.c
	mkdir -p $(@D)
	${CC} ${CFLAGS} ${INC_FLAGS} -c $< -o $@

all: $(NAME)

${NAME}: $(LIBFT) $(MLX) ${OBJ_FILES}
	${CC} ${CFLAGS} ${INC_FLAGS} ${OBJ_FILES} ${LIB_FLAGS} -o ${NAME}


clean:
	$(RM) $(OBJS)
	make clean -C $(LIBFT_PATH)
	make clean -C $(MLX_PATH)
	@echo "\033[33;32m=== so_long object files deleted \t\t\t\tDONE\e[0m"

fclean:	clean
	$(RM) $(NAME)
	make fclean -C $(LIBFT_PATH)
	@echo "\033[33;32m=== so_long bin file deleted \t\t\tDONE\e[0m"

re: fclean all

.PHONY: clean fclean re all

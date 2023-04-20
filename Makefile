#*************************************************************************** #
#                                                                              #
#            :::      ::::::::                                                 #
#          :+:      :+:    :+:                                                 #
#        +:+ +:+         +:+         Makefile v2.1                             #
#      +#+  +:+       +#+                                                      #
#    +#+#+#+#+#+   +#+               By: troberts <troberts@student.42.fr>     #
#         #+#    #+#                                                           #
#        ###   ########.fr                                                     #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                              VARIABLE REFERENCE                              #
# **************************************************************************** #

NAME= cub3D

#CC= clang
CFLAGS= -Wall -Werror -Wextra -g3 $(INCLUDE)
LDFLAGS= -L$(MLX_DIR) -L$(LIBFT_DIR) -lmlx -lXext -lX11 -lm

INCLUDE = -I$(INCLUDE_DIR) -I$(LIBFT_DIR) -I$(LIBFT_INC) -I$(MLX_DIR)

LIBFT_DIR= libft
LIBFT_LIB= $(LIBFT_DIR)/libft.a
LIBFT_INC= $(LIBFT_DIR)/includes

MLX_DIR= mlx
MLX_LIB= $(MLX_DIR)/libmlx_Linux.a

INCLUDE_DIR= include
OBJ_DIR= obj/
SRC_DIR= src/

# **************************************************************************** #
#                                .C & .H FILES                                 #
# **************************************************************************** #

SRC_FILE=	\
			engine/draw.c \
			engine/free_mlx.c \
			engine/game_utils.c \
			engine/game.c \
			engine/init_draw.c \
			engine/minimap.c \
			engine/move.c \
			engine/raycast.c \
			\
			parser/parser_check.c \
			parser/parser_map.c \
			parser/parser_utils.c \
			parser/parser.c \
			parser/read_file.c \
			\
			clean.c \
			error.c \
			free.c \
			handle.c \
			init.c \
			main.c \
			utils.c

SRC=		$(addprefix $(SRC_DIR), $(SRC_FILE))
OBJ=		$(addprefix obj/, ${SRC_FILE:.c=.o})

# **************************************************************************** #
#                                HEADER CONFIG                                 #
# **************************************************************************** #

#                 # <-- start here         | <-- middle             # <-- stop here
HEADER_NAME 	= +                      Cub3D                      #

COLOR_RED		= \033[0;31m
COLOR_GREEN		= \033[0;32m
COLOR_YELLOW	= \033[0;33m
COLOR_BLUE		= \033[0;34m
COLOR_PURPLE	= \033[0;35m
COLOR_CYAN		= \033[0;36m
COLOR_WHITE		= \033[0;37m
COLOR_END		= \033[m

HEADER =		@echo "${COLOR_CYAN}\
				\n/* ************************************************************************** */\
				\n/*                                                                            */\
				\n/*            :::      ::::::::                                               */\
				\n/*          :+:      :+:    :+:                                               */\
				\n/*        +:+ +:+         +:${HEADER_NAME}*/\
				\n/*      +\#+  +:+       +\#+                                                    */\
				\n/*    +\#+\#+\#+\#+\#+   +\#+                    <aquincho@student.42.fr>           */\
				\n/*         \#+\#    \#+\#                     <troberts@student.42.fr>            */\
				\n/*        \#\#\#   \#\#\#\#\#\#\#\#.fr                                                   */\
				\n/*                                                                            */\
				\n/* ************************************************************************** */\
				\n \
				\n${COLOR_END}"

HEADER_VAR =	@echo "${COLOR_CYAN}\
				\n \
				BINARY NAME: $(NAME) \
				\n CC: $(CC) \
				\n CFLAGS: $(CFLAGS) \
				\n LDFLAGS: $(LDFLAGS) \
				\n${COLOR_END}"

# **************************************************************************** #
#                                    RULES                                     #
# **************************************************************************** #

all: $(NAME)

$(NAME): FORCE header
	$(HEADER_VAR)
	@echo -n "${COLOR_PURPLE}Creating libf : \n[${COLOR_END}"
	@$(MAKE) --no-print-directory --silent $(LIBFT_LIB)
	@echo -n "${COLOR_PURPLE}]\n\n${COLOR_END}"
	@echo -n "${COLOR_BLUE}Creating mlx : \n${COLOR_END}"
	@$(MAKE) --no-print-directory --silent $(MLX_LIB)
	@echo -n "${COLOR_BLUE}\n\n${COLOR_END}"
	@echo -n "${COLOR_YELLOW}Compiling : \n[${COLOR_END}"
	@$(MAKE) --no-print-directory --silent $(OBJ)
	@echo -n "${COLOR_YELLOW}]\n\n${COLOR_END}"
	@echo -n "${COLOR_GREEN}Linking : "
	@$(CC) -o $@ $(OBJ) $(LDFLAGS) $(LIBFT_LIB)
	@echo "${COLOR_GREEN}Done. ${COLOR_END}"

FORCE: ;

bonus: $(NAME)

$(LIBFT_LIB): makelibf ;

makelibf :
	make -C $(LIBFT_DIR)

$(MLX_LIB): makemlx ;

makemlx :
	make -C $(MLX_DIR)

$(OBJ): $(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@echo -n "${COLOR_YELLOW}#${COLOR_END}"
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

reobj: FORCE header cleanobj
	$(HEADER_VAR)
	@echo -n "${COLOR_YELLOW}Compiling : \n[${COLOR_END}"
	@$(MAKE) --no-print-directory --silent $(OBJ)
	@echo -n "${COLOR_YELLOW}]\n\n${COLOR_END}"
	@echo -n "${COLOR_GREEN}Linking : "
	@$(CC) -o $@ $(OBJ) $(LDFLAGS) $(LIBFT_LIB)
	@echo "${COLOR_GREEN}Done. ${COLOR_END}"

header:
	$(HEADER)

cleanobj:
	@rm -f $(OBJ)

cleanobjdir: cleanobj
	@rm -rf $(OBJ_DIR)

cleanlibft:
	@make -C $(LIBFT_DIR) clean
	make -C $(MLX_DIR) clean

fcleanlibft:
	@make -C $(LIBFT_DIR) fclean

clean: header
	@echo "${COLOR_RED}Removing libs objects.${COLOR_END}"
	@$(MAKE) --no-print-directory --silent cleanlibft
	@echo "${COLOR_RED}Removing objects.${COLOR_END}"
	@$(MAKE) --no-print-directory --silent cleanobj
	@echo "${COLOR_RED}Removing object directory.${COLOR_END}"
	@$(MAKE) --no-print-directory --silent cleanobjdir

fclean: clean
	@echo "${COLOR_RED}Removing libs binary files.${COLOR_END}"
	@$(MAKE) --no-print-directory --silent fcleanlibft
	@echo "${COLOR_RED}Removing binary file.${COLOR_END}"
	@rm -f $(NAME) $(NAME_BONUS)

re: header fclean all

# reobj: cleanobj
# 	make -C .

norm: header
	@echo -n "$(COLOR_GREEN)"
	-python3 -m norminette $(SRC_DIR)
	@echo "$(COLOR_PURPLE)"
	-python3 -m norminette $(INCLUDE_DIR)
	@echo -n "$(COLOR_END)"

.PHONY: all clean fclean re reobj norm header cleanobj bonus FORCE makelibf makemlx cleanobjdir cleanlibft fcleanlibft

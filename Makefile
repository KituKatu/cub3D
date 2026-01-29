# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmcgrane <jmcgrane@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/14 17:10:46 by adecheri          #+#    #+#              #
#    Updated: 2026/01/28 16:11:32 by jmcgrane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

## Commands ##
CC = cc
INCLUDES = -I ./inc -I $(LIBMLX)/include
CFLAGS = -Wall -Wextra -Werror -Wunreachable-code -Ofast -fPIE -MMD -MP $(INCLUDES) #-g -fsanitize=thread
# CFLAGS = -Wall -Wextra -Werror -Wunreachable-code -Ofast -MMD -MP $(INCLUDES) #-g -fsanitize=thread
##CFLAGS = -I/opt/homebrew/include -L/opt/homebrew/lib -lglfw -framework OpenGL $(INCLUDES)
LIBDIR = lib/
LIBFT_DIR = $(LIBDIR)libft/
LIBFT	= $(LIBFT_DIR)libft.a
LIBMLX = $(LIBDIR)MLX42
LIBS = $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
LDFLAGS = -L$(LIBFT_DIR) -lft
RM = rm -f
RMDIR = rm -rf
MKDIR = mkdir -p


## Files ##
MAINDIR = src/main/
PARSDIR = src/parsing/
RAYDIR = src/raycasting/
UTILDIR = src/utils/
MLXDIR = src/mlx/

SRCS =	$(MAINDIR)main.c \
		$(PARSDIR)parse_map.c \
		$(PARSDIR)parse_colors.c \
		$(PARSDIR)parsing_utils.c \
		$(PARSDIR)read_map.c \
		$(RAYDIR)raycasting.c \
		$(UTILDIR)error.c \
		$(UTILDIR)free.c \
		$(MLXDIR)init_mlx.c \
		
OBJS = $(SRCS:src/%.c=obj/%.o)
DEPS = $(OBJS:.o=.d)


## Targets ##
.PHONY: all clean fclean re libmlx

all: submodules libmlx $(NAME)

# Target to initialize and update submodules
submodules:
	git submodule update --init --recursive

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(NAME): obj $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBFT) $(LIBS)

obj:
	@$(MKDIR) obj

obj/%.o: src/%.c
	@$(MKDIR) $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

-include $(DEPS)

clean:
	$(RM) $(OBJS) $(DEPS)	
	$(RMDIR) $(LIBMLX)/build
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) all

#debugging 
leak:
	$(MAKE) -s debug
	valgrind --suppressions=inc/mlx42.supp --track-fds=yes --track-origins=yes \
	--leak-check=full --show-leak-kinds=all ./$(NAME) $(INPUT)
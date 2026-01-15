# **************************************************************************** #
#                                                                              #
#                                                          ::::::::            #
#    Makefile                                            :+:    :+:            #
#                                                       +:+                    #
#    By: adecheri <marvin@42.fr>                       +#+                     #
#                                                     +#+                      #
#    Created: 2026/01/14 17:10:46 by adecheri       #+#    #+#                 #
#    Updated: 2026/01/14 17:10:48 by adecheri       ########   odam.nl         #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

## Commands ##
CC = cc
INCLUDES = -I ./inc -I $(LIBMLX)/include
CFLAGS = -Wall -Wextra -Werror -Wunreachable-code -Ofast -MMD -MP $(INCLUDES) #-g -fsanitize=thread
##CFLAGS = -I/opt/homebrew/include -L/opt/homebrew/lib -lglfw -framework OpenGL $(INCLUDES)
LIBDIR = lib/
LIBFT_DIR = $(LIBDIR)libft/
LIBFT	= $(LIBFT_DIR)libft.a
LIBMLX = $(LIBDIR)MLX42
LIBS = $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
LDFLAGS = -L/libft -lft
RM = rm -f
RMDIR = rm -rf
MKDIR = mkdir -p


## Files ##
SRCS = src/main.c
		
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

$(NAME): obj $(OBJS) libft/libft.a
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS) $(LIBS)

obj:
	@$(MKDIR) obj

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

-include $(DEPS)

clean:
	$(RM) $(OBJS) $(DEPS)	
	$(RMDIR) $(LIBMLX)/build
	$(MAKE) -C libft clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C libft fclean

re: fclean all

libft/libft.a:
	$(MAKE) -C libft all

#debugging 
leak:
	$(MAKE) -s debug
	valgrind --suppressions=inc/mlx42.supp --track-fds=yes --track-origins=yes \
	--leak-check=full --show-leak-kinds=all ./$(NAME) $(INPUT)
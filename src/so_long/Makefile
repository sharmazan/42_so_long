NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT_PATH = ../libft
LIBFT_LIB = $(LIBFT_PATH)/libft.a
GNL_PATH = ../gnl
MLX_PATH = ../minilibx-linux
MLX_LIB = $(MLX_PATH)/libmlx.a
HEADERS = so_long.h $(GNL_PATH)/get_next_line.h
CPPFLAGS = -I../minilibx-linux
LDFLAGS = -L$(MLX_PATH) -L$(LIBFT_PATH)
LDLIBS = -lmlx -lft -lXext -lX11 -lm -lz


SOURCES =	so_long.c \
			helpers.c \
			startup.c \
			move.c \
			map_load.c \
			map_validate.c \
			map_path.c \
			render.c \
			$(GNL_PATH)/get_next_line.c

OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(MLX_LIB) $(LIBFT_LIB) $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) $(LDLIBS) -o $(NAME)

$(MLX_LIB):
	$(MAKE) -C $(MLX_PATH)

$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_PATH)

%.o: %.c $(HEADERS)
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ -c $<

fclean: clean
	rm -f $(NAME)

clean:
	rm -f $(OBJECTS)

re: fclean all

.PHONY: all clean tests re fclean

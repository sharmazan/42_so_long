NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT_PATH = ../libft
LIBFT_LIB = $(LIBFT_PATH)/libft.a
GNL_PATH = ../gnl
MLX_CPPFLAGS ?=
MLX_LDFLAGS ?=
MLX_LDLIBS ?= -lmlx -lXext -lX11 -lm -lz
HEADERS = so_long.h $(GNL_PATH)/get_next_line.h
CPPFLAGS = $(MLX_CPPFLAGS)
LDFLAGS = $(MLX_LDFLAGS) -L$(LIBFT_PATH)
LDLIBS = -lft $(MLX_LDLIBS)


SOURCES =	so_long.c \
			helpers.c \
			cleanup.c \
			startup.c \
			events.c \
			move.c \
			map_load.c \
			map_validate.c \
			map_path_verification.c \
			render.c \
			render_map.c \
			$(GNL_PATH)/get_next_line.c

OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)


$(NAME): $(LIBFT_LIB) $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) $(LDLIBS) -o $(NAME)

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

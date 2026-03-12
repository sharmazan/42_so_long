NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT_PATH = ../libft
LIBFT_LIB = $(LIBFT_PATH)/libft.a
FTPRINTF_PATH = ../ft_printf
FTPRINTF_LIB = $(FTPRINTF_PATH)/libftprintf.a
MLX_PATH = ../minilibx-linux
MLX_LIB = $(MLX_PATH)/libmlx.a
HEADER = ../inc/ft_header.h
CPPFLAGS = -I../inc -I../minilibx-linux
LDFLAGS = -L$(MLX_PATH) -L$(FTPRINTF_PATH) -L$(LIBFT_PATH)
LDLIBS = -lmlx -lftprintf -lft -lXext -lX11 -lm -lz


SOURCES =	so_long.c

OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(MLX_LIB) $(FTPRINTF_LIB) $(LIBFT_LIB) $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) $(LDLIBS) -o $(NAME)

$(MLX_LIB):
	$(MAKE) -C $(MLX_PATH)

$(FTPRINTF_LIB):
	$(MAKE) -C $(FTPRINTF_PATH)

$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_PATH)

%.o: %.c $(HEADER)
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ -c $<

fclean: clean
	rm -f $(NAME)

clean:
	rm -f $(OBJECTS)

re: fclean all

.PHONY: all clean tests re fclean

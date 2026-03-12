NAME = so_long
SRC_PATH = src
CC = cc
CFLAGS = -Wall -Wextra -Werror

SO_LONG_PATH = $(SRC_PATH)/$(NAME)
LIBFT_PATH = $(SRC_PATH)/libft
LIBFT_LIB = $(LIBFT_PATH)/libft.a
FTPRINTF_PATH = $(SRC_PATH)/ft_printf
FTPRINTF_LIB = $(FTPRINTF_PATH)/libftprintf.a
MLX_PATH = $(SRC_PATH)/minilibx-linux
MLX_LIB = $(MLX_PATH)/libmlx.a
HEADER = src/inc/ft_header.h

all: $(NAME)

$(NAME): $(MLX_LIB) $(FTPRINTF_LIB) $(LIBFT_LIB) $(HEADER)
	$(MAKE) -C $(SO_LONG_PATH) CC="$(CC)" CFLAGS="$(CFLAGS)"
	cp $(SO_LONG_PATH)/$(NAME) .

$(MLX_LIB):
	$(MAKE) -C $(MLX_PATH)

$(FTPRINTF_LIB):
	$(MAKE) -C $(FTPRINTF_PATH) CC="$(CC)" CFLAGS="$(CFLAGS)"

$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_PATH) CC="$(CC)" CFLAGS="$(CFLAGS)"

debug: CFLAGS += -g3 -O0
debug: re

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_PATH) fclean
	$(MAKE) -C $(FTPRINTF_PATH) fclean
	$(MAKE) -C $(SO_LONG_PATH) fclean

clean:
	if [ -f $(MLX_PATH)/Makefile.gen ]; then $(MAKE) -C $(MLX_PATH) clean; fi
	$(MAKE) -C $(LIBFT_PATH) clean
	$(MAKE) -C $(FTPRINTF_PATH) clean
	$(MAKE) -C $(SO_LONG_PATH) clean

re: fclean all

.PHONY: all clean tests re fclean debug

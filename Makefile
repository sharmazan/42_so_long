NAME = so_long
SRC_PATH = src
CC = cc
CFLAGS = -Wall -Wextra -Werror

SO_LONG_PATH = $(SRC_PATH)/$(NAME)
SO_LONG_SOURCES = $(wildcard $(SO_LONG_PATH)/*.c)
SO_LONG_HEADERS = $(wildcard $(SO_LONG_PATH)/*.h)
GNL_PATH = $(SRC_PATH)/gnl
GNL_SOURCES = $(wildcard $(GNL_PATH)/*.c)
GNL_HEADERS = $(wildcard $(GNL_PATH)/*.h)
LIBFT_PATH = $(SRC_PATH)/libft
LIBFT_LIB = $(LIBFT_PATH)/libft.a
MLX_PATH = $(SRC_PATH)/minilibx-linux
MLX_LIB = $(MLX_PATH)/libmlx.a

all: $(NAME)

$(NAME): $(MLX_LIB) $(LIBFT_LIB) $(SO_LONG_SOURCES) \
	$(SO_LONG_HEADERS) $(GNL_SOURCES) $(GNL_HEADERS) $(SO_LONG_PATH)/Makefile
	$(MAKE) -C $(SO_LONG_PATH) CC="$(CC)" CFLAGS="$(CFLAGS)"
	cp $(SO_LONG_PATH)/$(NAME) .

$(MLX_LIB):
	$(MAKE) -C $(MLX_PATH)

$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_PATH) CC="$(CC)" CFLAGS="$(CFLAGS)"

debug: CFLAGS += -g3 -O0
debug: re

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_PATH) fclean
	$(MAKE) -C $(SO_LONG_PATH) fclean

clean:
	if [ -f $(MLX_PATH)/Makefile.gen ]; then $(MAKE) -C $(MLX_PATH) clean; fi
	$(MAKE) -C $(LIBFT_PATH) clean
	$(MAKE) -C $(SO_LONG_PATH) clean

re: fclean all

.PHONY: all clean tests re fclean debug

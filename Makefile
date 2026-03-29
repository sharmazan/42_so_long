NAME = so_long
SRC_PATH = src
CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX_CPPFLAGS ?=
MLX_LDFLAGS ?=
MLX_LDLIBS ?= -lmlx -lXext -lX11 -lm -lz

SO_LONG_PATH = $(SRC_PATH)/$(NAME)
SO_LONG_SOURCES = $(wildcard $(SO_LONG_PATH)/*.c)
SO_LONG_HEADERS = $(wildcard $(SO_LONG_PATH)/*.h)
GNL_PATH = $(SRC_PATH)/gnl
GNL_SOURCES = $(wildcard $(GNL_PATH)/*.c)
GNL_HEADERS = $(wildcard $(GNL_PATH)/*.h)
LIBFT_PATH = $(SRC_PATH)/libft
LIBFT_LIB = $(LIBFT_PATH)/libft.a
NORM_PATHS = $(SO_LONG_PATH) $(GNL_PATH) $(LIBFT_PATH)

all: $(NAME)

$(NAME): $(LIBFT_LIB) $(SO_LONG_SOURCES) \
	$(SO_LONG_HEADERS) $(GNL_SOURCES) $(GNL_HEADERS) $(SO_LONG_PATH)/Makefile
	$(MAKE) -C $(SO_LONG_PATH) CC="$(CC)" CFLAGS="$(CFLAGS)" \
		MLX_CPPFLAGS="$(MLX_CPPFLAGS)" MLX_LDFLAGS="$(MLX_LDFLAGS)" \
		MLX_LDLIBS="$(MLX_LDLIBS)"
	cp $(SO_LONG_PATH)/$(NAME) .

$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_PATH) CC="$(CC)" CFLAGS="$(CFLAGS)"

debug: CFLAGS += -g3 -O0
debug: re

norm:
	norminette --use-gitignore $(NORM_PATHS)

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_PATH) fclean
	$(MAKE) -C $(SO_LONG_PATH) fclean

clean:
	$(MAKE) -C $(LIBFT_PATH) clean
	$(MAKE) -C $(SO_LONG_PATH) clean

re: fclean all

.PHONY: all clean tests re fclean debug norm

NAME = so_long
SRC_PATH = src
CC = cc
CFLAGS = -Wall -Wextra -Werror

SO_LONG_PATH = $(SRC_PATH)/$(NAME)
LIBFT_PATH = $(SRC_PATH)/libft
LIBFT_LIB = $(LIBFT_PATH)/libft.a
FTPRINTF_PATH = $(SRC_PATH)/ft_printf
FTPRINTF_LIB = $(FTPRINTF_PATH)/libftprintf.a
HEADER = src/inc/ft_header.h

SO_LONG_SOURCES = $(SO_LONG_PATH)/so_long.c
SO_LONG_OBJECTS = $(SO_LONG_SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(FTPRINTF_LIB) $(LIBFT_LIB) $(SO_LONG_OBJECTS) $(HEADER)
	$(MAKE) -C $(SO_LONG_PATH) CC="$(CC)" CFLAGS="$(CFLAGS)"
	cp $(SO_LONG_PATH)/$(NAME) .

$(FTPRINTF_LIB):
	$(MAKE) -C $(FTPRINTF_PATH) CC="$(CC)" CFLAGS="$(CFLAGS)"

$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_PATH) CC="$(CC)" CFLAGS="$(CFLAGS)"

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

debug: CFLAGS += -g3 -O0
debug: re

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_PATH) fclean
	$(MAKE) -C $(FTPRINTF_PATH) fclean
	$(MAKE) -C $(SO_LONG_PATH) fclean

clean:
	$(MAKE) -C $(LIBFT_PATH) clean
	$(MAKE) -C $(FTPRINTF_PATH) clean
	$(MAKE) -C $(SO_LONG_PATH) clean

re: fclean all

.PHONY: all clean tests re fclean debug

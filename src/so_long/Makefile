NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT_PATH = ../libft
LIBFT_LIB = $(LIBFT_PATH)/libft.a
FTPRINTF_PATH = ../ft_printf
FTPRINTF_LIB = $(FTPRINTF_PATH)/libftprintf.a
HEADER = ../inc/ft_header.h


SOURCES =	so_long.c

OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(FTPRINTF_LIB) $(LIBFT_LIB) $(OBJECTS) $(HEADER)
	$(CC) -o $(NAME) $(OBJECTS) $(FTPRINTF_LIB) $(LIBFT_LIB)

$(FTPRINTF_LIB):
	$(MAKE) -C $(FTPRINTF_PATH)

$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_PATH)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -o $@ -c $<

fclean: clean
	rm -f $(NAME)

clean:
	rm -f $(OBJECTS)

re: fclean all

.PHONY: all clean tests re fclean

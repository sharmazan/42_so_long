NAME = libftprintf.a
HEADER = libftprintf.h
CC = cc
CFLAGS = -Wall -Wextra -Werror

SOURCES =	ft_printf.c \
			utils.c \
			helper.c

OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	ar rcs $(NAME) $?

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -o $@ -c $<

fclean: clean
	rm -f $(NAME)

clean:
	rm -f $(OBJECTS)

re: fclean all

.PHONY: all clean tests re fclean

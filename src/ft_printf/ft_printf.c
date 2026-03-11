/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssharmaz <ssharmaz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 23:17:00 by ssharmaz          #+#    #+#             */
/*   Updated: 2026/01/12 16:14:17 by ssharmaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helper.h"
#include "libftprintf.h"
#include "utils.h"
#include <stdarg.h>
#include <unistd.h>

static int	ft_print_formated(int fd, va_list args, char c)
{
	if (c == 'c')
	{
		c = (char)va_arg(args, int);
		return (write(fd, &c, 1));
	}
	else if (c == 's')
		return (ft_putstr_fd(va_arg(args, char *), fd));
	else if (c == 'i' || c == 'd')
		return (ft_putnbr_fd(va_arg(args, int), fd));
	else if (c == 'u')
		return (ft_putdec_fd(va_arg(args, unsigned int), fd));
	else if (c == 'p')
		return (ft_putptr_fd(va_arg(args, void *), fd));
	else if (c == 'x')
		return (ft_puthex_fd(va_arg(args, unsigned int), fd));
	else if (c == 'X')
		return (ft_putbighex_fd(va_arg(args, unsigned int), fd));
	else if (c == '%')
		return (write(fd, "%", 1));
	return (0);
}

int	ft_fprintf(int fd, const char *format, ...)
{
	va_list	args;
	int		printed;

	printed = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			printed += ft_print_formated(fd, args, *format);
			format++;
		}
		else
			printed += write(fd, format++, 1);
	}
	va_end(args);
	return (printed);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		printed;

	printed = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			printed += ft_print_formated(STDOUT, args, *format);
			format++;
		}
		else
			printed += write(STDOUT, format++, 1);
	}
	va_end(args);
	return (printed);
}

/*
#include <stdio.h>

void	test_char(void)
{
	int		i;
	int		j;
	char	c;

	c = 0;
	i = printf("%c\n", c);
	j = ft_printf("%c\n", c);
	ft_printf("Original: [%i], ft_print: [%i]\n", i, j);
	i = printf("%c\n", -15);
	j = ft_printf("%c\n", -15);
	ft_printf("Original: [%i], ft_print: [%i]\n", i, j);
	i = printf("%c\n", '\n');
	j = ft_printf("%c\n", '\n');
	ft_printf("Original: [%i], ft_print: [%i]\n", i, j);
	for (c = '0'; c <= '9'; c++)
	{
		i = printf("%c\n", c);
		j = ft_printf("%c\n", c);
		ft_printf("Original: [%i], ft_print: [%i]\n", i, j);
	}
}

void	test_dec(void)
{
	int	i;
	int	j;
	int	n;

	n = -2147483648;
	i = printf("%d\n", 0);
	j = ft_printf("%d\n", 0);
	ft_printf("Original: [%i], ft_print: [%i]\n", i, j);
	i = printf("%d\n", -15);
	j = ft_printf("%d\n", -15);
	ft_printf("Original: [%i], ft_print: [%i]\n", i, j);
	i = printf("%d\n", 15);
	j = ft_printf("%d\n", 15);
	ft_printf("Original: [%i], ft_print: [%i]\n", i, j);
	i = printf("%d\n", n);
	j = ft_printf("%d\n", n);
	ft_printf("Original: [%i], ft_print: [%i]\n", i, j);
	i = printf("%d\n", 2147483647);
	j = ft_printf("%d\n", 2147483647);
	ft_printf("Original: [%i], ft_print: [%i]\n", i, j);
}

void	test_int(void)
{
	int	n;
	int	i;
	int	j;

	n = -2147483648;
	i = printf("%i\n", 0);
	j = ft_printf("%i\n", 0);
	ft_printf("Original: [%i], ft_print: [%i]\n", i, j);
	i = printf("%i\n", -15);
	j = ft_printf("%i\n", -15);
	ft_printf("Original: [%i], ft_print: [%i]\n", i, j);
	i = printf("%i\n", 15);
	j = ft_printf("%i\n", 15);
	ft_printf("Original: [%i], ft_print: [%i]\n", i, j);
	i = printf("%i\n", n);
	j = ft_printf("%i\n", n);
	ft_printf("Original: [%i], ft_print: [%i]\n", i, j);
	i = printf("%i\n", 2147483647);
	j = ft_printf("%i\n", 2147483647);
	ft_printf("Original: [%i], ft_print: [%i]\n", i, j);
}

void	test_hex(void)
{
	int	n;
	int	i;
	int	j;

	n = -2147483648;
	i = printf("%x\n", 0);
	j = ft_printf("%x\n", 0);
	ft_printf("Original: [%i], ft_print: [%i]\n", i, j);
	i = printf("%x\n", -15);
	j = ft_printf("%x\n", -15);
	ft_printf("Original: [%i], ft_print: [%i]\n", i, j);
	i = printf("%x\n", 15);
	j = ft_printf("%x\n", 15);
	ft_printf("Original: [%i], ft_print: [%i]\n", i, j);
	i = printf("%x\n", n);
	j = ft_printf("%x\n", n);
	ft_printf("Original: [%i], ft_print: [%i]\n", i, j);
	i = printf("%x\n", 2147483647);
	j = ft_printf("%x\n", 2147483647);
	ft_printf("Original: [%i], ft_print: [%i]\n", i, j);
}

void	test_bighex(void)
{
	unsigned int	n;
	int				i;
	int				j;

	n = -1;
	i = printf("%X\n", 0);
	j = ft_printf("%X\n", 0);
	ft_printf("Original: [%i], ft_print: [%i]\n", i, j);
	i = printf("%X\n", -15);
	j = ft_printf("%X\n", -15);
	ft_printf("Original: [%i], ft_print: [%i]\n", i, j);
	i = printf("%X\n", 15);
	j = ft_printf("%X\n", 15);
	ft_printf("Original: [%i], ft_print: [%i]\n", i, j);
	i = printf("%X\n", n);
	j = ft_printf("%X\n", n);
	ft_printf("Original: [%i], ft_print: [%i]\n", i, j);
	i = printf("%X\n", (unsigned int)2147483647);
	j = ft_printf("%X\n", (unsigned int)2147483647);
	ft_printf("Original: [%i], ft_print: [%i]\n", i, j);
}

void	test_str(void)
{
	char	*str;
	int		i;
	int		j;

	str = NULL;
	i = printf("%s\n", str);
	j = ft_printf("%s\n", str);
	ft_printf("Original: [%i], ft_print: [%i]\n", i, j);
	str = "Hello";
	i = printf("%s\n", str);
	j = ft_printf("%s\n", str);
	ft_printf("Original: [%i], ft_print: [%i]\n", i, j);
}

void	test_ptr(void)
{
	void	*str;
	int		i;
	int		j;

	str = "Hello";
	i = printf("%p\n", NULL);
	j = ft_printf("%p\n", NULL);
	ft_printf("Original: [%i], ft_print: [%i]\n", i, j);
	i = printf("%p\n", str);
	j = ft_printf("%p\n", str);
	ft_printf("Original: [%i], ft_print: [%i]\n", i, j);
}

// #include "helper.c"
// #include "utils.c"

int	main(void)
{
	char	*str;
	int		i;
	int		j;

	str = NULL;
	ft_printf("***************************************\n");
	ft_printf("Testing char\n");
	ft_printf("***************************************\n");
	test_char();
	ft_printf("***************************************\n");
	ft_printf("Testing int\n");
	ft_printf("***************************************\n");
	test_int();
	ft_printf("***************************************\n");
	ft_printf("Testing dec\n");
	ft_printf("***************************************\n");
	test_dec();
	ft_printf("***************************************\n");
	ft_printf("Testing str\n");
	ft_printf("***************************************\n");
	test_str();
	ft_printf("***************************************\n");
	ft_printf("Testing hex\n");
	ft_printf("***************************************\n");
	test_hex();
	ft_printf("***************************************\n");
	ft_printf("Testing HEX\n");
	ft_printf("***************************************\n");
	test_bighex();
	ft_printf("***************************************\n");
	ft_printf("Testing ptr\n");
	ft_printf("***************************************\n");
	test_ptr();
	ft_printf("***************************************\n");
	ft_printf("Testing mix\n");
	ft_printf("***************************************\n");
	j = ft_printf("%s %c %s %d %i %u %u %x %X %x %% %p world!!!!\n", str, 'A',
			"BBB", -12, 12, -1, 1, 15, 255, -15, str);
	i = printf("%s %c %s %d %i %u %u %x %X %x %% %p world!!!!\n", str, 'A',
			"BBB", -12, 12, -1, 1, 15, 255, -15, str);
	ft_printf("Original: [%i], ft_print: [%i]\n", i, j);
	return (0);
}
*/

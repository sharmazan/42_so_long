/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssharmaz <ssharmaz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 23:17:00 by ssharmaz          #+#    #+#             */
/*   Updated: 2025/10/15 18:09:16 by ssharmaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static long	ft_pow(int base, int power)
{
	long	n;

	n = 1;
	if (power >= 0)
		while (power-- > 0)
			n *= base;
	else
		return (0);
	return (n);
}

static unsigned char	calc_chars(int n)
{
	unsigned char	size;
	long			num;

	num = n;
	size = 1;
	if (n < 0)
		num *= -1;
	while (ft_pow(10, size) <= num)
		size++;
	return (size);
}

static long	ft_abs(int n)
{
	if (n < 0)
		return (-1 * (long)n);
	else
		return (n);
}

char	*ft_itoa(int n)
{
	char			*p;
	unsigned char	size;
	long			num;
	int				minus;

	num = ft_abs(n);
	size = calc_chars(n);
	if (n < 0)
		minus = 1;
	else
		minus = 0;
	p = malloc(size + minus + 1);
	if (!p)
		return (NULL);
	p[size + minus] = 0;
	if (minus)
		p[0] = '-';
	while (size--)
	{
		p[size + minus] = num % 10 + '0';
		num /= 10;
	}
	return (p);
}

/*
int	main(void)
{
	// printf("%ld\n", ft_pow(10, 3));
	// printf("%d\n", -11 % 10);
	printf("%s\n", ft_itoa(0));
	printf("%s\n", ft_itoa(1000));
	printf("%s\n", ft_itoa(-123));
	printf("%s\n", ft_itoa(2147483647));
	printf("%s\n", ft_itoa(-2147483648));
	return (0);
}
*/

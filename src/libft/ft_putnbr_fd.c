/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssharmaz <ssharmaz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 23:17:00 by ssharmaz          #+#    #+#             */
/*   Updated: 2025/10/14 19:41:44 by ssharmaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_putnbr_fd(int n, int fd)
{
	char	c;
	int		base;
	int		print;

	print = 0;
	base = -1000000000;
	if (n < 0)
		write(fd, "-", 1);
	else
		n = -n;
	while (base)
	{
		if (n <= base)
		{
			print = 1;
			c = n / base + '0';
			write(fd, &c, 1);
			n %= base;
		}
		else if (print)
			write(fd, "0", 1);
		base /= 10;
	}
	if (!print)
		write(fd, "0", 1);
}

/*
int	main(void)
{
	// printf("%d\n", -101 % -10);
	// printf("%d\n", -101 / -100);
	// return (0);
	ft_putnbr_fd(0, 1);
	// 2147483647
	// ft_putnbr_fd(-987441, 1);
	// ft_putnbr_fd(-10000, 1);
	// ft_putnbr_fd(-2147483647, 1);
	// ft_putnbr_fd(2147483647, 1);
	// write(1, "\n", 1);
	return (0);
}
*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssharmaz <ssharmaz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 23:17:00 by ssharmaz          #+#    #+#             */
/*   Updated: 2025/11/04 19:22:22 by ssharmaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <unistd.h>

int	ft_putdec_fd(unsigned int n, int fd)
{
	return (ft_putnum_base(n, "0123456789", fd));
}

int	ft_putnbr_fd(int n, int fd)
{
	int		printed;
	long	num;

	if (n >= 0)
		return (ft_putnum_base(n, "0123456789", fd));
	num = n;
	num = -num;
	printed = write(fd, "-", 1);
	printed += ft_putnum_base(num, "0123456789", fd);
	return (printed);
}

int	ft_puthex_fd(size_t n, int fd)
{
	return (ft_putnum_base(n, "0123456789abcdef", fd));
}

int	ft_putbighex_fd(size_t n, int fd)
{
	return (ft_putnum_base(n, "0123456789ABCDEF", fd));
}

int	ft_putptr_fd(void *ptr, int fd)
{
	if (!ptr)
		return (ft_putstr_fd("(nil)", fd));
	write(fd, "0x", 2);
	return (ft_puthex_fd((size_t)ptr, fd) + 2);
}

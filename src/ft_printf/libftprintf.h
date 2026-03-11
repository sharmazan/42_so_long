/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssharmaz <ssharmaz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 23:17:00 by ssharmaz          #+#    #+#             */
/*   Updated: 2026/01/12 16:15:59 by ssharmaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <stddef.h>
# ifndef STDOUT
#  define STDOUT 1
# endif

int	ft_fprintf(int fd, const char *format, ...);
int	ft_printf(const char *format, ...);
int	ft_putstr_fd(char *s, int fd);
int	ft_putnbr_fd(int n, int fd);
int	ft_putdec_fd(unsigned int n, int fd);
int	ft_puthex_fd(size_t n, int fd);
int	ft_putbighex_fd(size_t n, int fd);
int	ft_putptr_fd(void *ptr, int fd);
int	ft_putnum_base(size_t n, char *base, int fd);

#endif

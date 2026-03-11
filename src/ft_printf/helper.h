/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssharmaz <ssharmaz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 23:17:00 by ssharmaz          #+#    #+#             */
/*   Updated: 2025/11/04 19:20:01 by ssharmaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HELPER_H
# define HELPER_H

# include <stddef.h>

int	ft_putnbr_fd(int n, int fd);
int	ft_putdec_fd(unsigned int n, int fd);
int	ft_puthex_fd(size_t n, int fd);
int	ft_putbighex_fd(size_t n, int fd);
int	ft_putptr_fd(void *ptr, int fd);

#endif

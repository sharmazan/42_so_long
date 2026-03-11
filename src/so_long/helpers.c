/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssharmaz <ssharmaz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 23:17:00 by ssharmaz          #+#    #+#             */
/*   Updated: 2026/03/09 16:05:00 by ssharmaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_header.h"
#include <unistd.h>

void	logmessage(char *s)
{
	while (*s)
		write(STDOUT, s++, 1);
	write(STDOUT, "\n", 1);
}

void	logerr(char *s)
{
	while (*s)
		write(STDERR, s++, 1);
	write(STDERR, "\n", 1);
}

void	errexit(char *s)
{
	logerr(s);
	exit(1);
}

void	clear_and_exit(int *a, t_list **stack_a, t_list **stack_b)
{
	free(a);
	ft_lstclear(stack_a, free);
	ft_lstclear(stack_b, free);
	exit(0);
}

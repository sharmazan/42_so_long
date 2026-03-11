/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_header.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssharmaz <ssharmaz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 23:17:00 by ssharmaz          #+#    #+#             */
/*   Updated: 2026/03/09 16:06:29 by ssharmaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_HEADER_H
# define FT_HEADER_H

# ifndef STDOUT
#  define STDOUT 1
# endif
# ifndef STDERR
#  define STDERR 2
# endif

# include "../ft_printf/libftprintf.h"
# include "../libft/libft.h"

int		sorted(t_list *stack);
void	pa(t_list **stackA, t_list **stackB);
void	pb(t_list **stackA, t_list **stackB);
void	ra(t_list **stack);
void	rb(t_list **stack);
void	rra(t_list **stack);
void	rrb(t_list **stack);
void	rotate(t_list **stack);
void	reverse_rotate(t_list **stack);
char	get_bit(int pos, unsigned int c);

void	logmessage(char *s);
void	logerr(char *s);
void	errexit(char *s);
void	print_number(void *number);
void	print_pointer(void *pointer);
int		stack_to_array(t_list *stack, int **a);
int		bits_in_number(int n);
int		is_duplicates(int *a, size_t len);
void	sort_array(int *a, size_t len);
void	verify_int(char *s);
int		index_in_array(int n, int *a, size_t len);
void	clear_and_exit(int *a, t_list **stack_a, t_list **stack_b);
void	verify_arguments_int(int ac, char **av);
void	store_numbers(int ac, char **av, t_list **stack);
void	verify_and_store_numbers(int ac, char **av, t_list **stack);

#endif

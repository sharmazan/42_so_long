/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_int_stack.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssharmaz <ssharmaz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 23:17:00 by ssharmaz          #+#    #+#             */
/*   Updated: 2026/03/09 15:26:41 by ssharmaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// typedef struct my_int_stack_struct
// {
// 	int							number;
// 	struct my_int_stack_struct	*next;
// }								my_stack;

// int	main(int ac, char **av)
// {
// 	my_stack	*stack;
// 	my_stack	*el;
// 	int			i;

// 	if (ac == 1)
// 	{
// 		printf("Provide one or more numbers\n");
// 		return (1);
// 	}
// 	stack = NULL;
// 	i = 1;
// 	while (i < ac)
// 	{
// 		el = malloc(sizeof(my_stack));
// 		el->number = atoi(av[i]);
// 		el->next = stack;
// 		stack = el;
// 		i++;
// 	}
// 	el = stack;
// 	while (el)
// 	{
// 		printf("Number is %d\n", el->number);
// 		el = el->next;
// 	}
// 	while (stack)
// 	{
// 		el = stack;
// 		stack = el->next;
// 		free(el);
// 	}
// 	return (0);
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vispinos <vispinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:03:49 by vispinos          #+#    #+#             */
/*   Updated: 2024/10/26 14:05:35 by vispinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	len_one(t_state *s)
{
	ft_putendl_fd("exit", 1);
	return (s->exit_code);
}

static int	not_num(void)
{
	ft_putendl_fd("exit\nminishell: exit: numeric argument required", 2);
	return (2);
}

static int	too_many_args(void)
{
	ft_putendl_fd("exit\nminishell: exit: too many arguments", 2);
	return (1);
}

static int	isnum(char *str)
{
	int	i;

	i = 0;
	while (ft_is_space(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (ft_isdigit(str[i]))
		i++;
	if (str[i])
		return (0);
	return (1);
}

int	ft_exit(char **array, t_state *s)
{
	int	len;
	int	code;

	len = sal(array);
	if (len == 1)
		code = len_one(s);
	else if (!isnum(array[1]))
		code = not_num();
	else if (len > 2)
		code = too_many_args();
	else
	{
		code = ft_atoi(array[1]) % 256;
		if (code < 0)
			code += 256;
		ft_putendl_fd("exit", 1);
	}
	return (code);
}

// int	main(int ac, char **av)
// {
// 	t_state	*s;

// 	s = malloc(sizeof(t_state));
// 	if (!s)
// 		return (1);
// 	s->exit_code = ft_exit(av, s);
// 	printf("Exit return code : %i\n", s->exit_code);
// 	if (ac)
// 		return (0);
// }

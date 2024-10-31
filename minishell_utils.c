/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcohen <tcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 18:07:02 by tcohen            #+#    #+#             */
/*   Updated: 2024/10/26 19:11:30 by tcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include <limits.h>
#include "signal/ft_signal.h"
#include "parsing/parsing.h"
#include "minishell.h"

t_state	*get_state(t_state *init)
{
	static t_state	*state = NULL;

	if (init != NULL)
		state = init;
	return (state);
}

int	is_empty_line(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_is_space(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	init_main(int ac, char **av, t_state *state)
{
	(void)ac;
	(void)av;
	get_state(state);
	state->exit_code = 0;
	state->test = 0;
	state->gc = new_gc(state);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcohen <tcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 17:57:09 by tcohen            #+#    #+#             */
/*   Updated: 2024/10/26 18:36:36 by tcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include <limits.h>
#include "signal/ft_signal.h"
#include "parsing/parsing.h"
#include "minishell.h"

int	g_signal = 0;

static int	sal2(char **array)
{
	int	i;

	if (!array)
		return (0);
	i = 0;
	while (array[i])
		i++;
	return (i);
}

static char	**append_char_star2(char **array, char *str, t_state *s)
{
	int		len;
	int		i;
	char	**new_array;

	len = sal2(array);
	new_array = ft_malloc(sizeof(char *) * (len + 2), &(s->gc), s);
	if (!new_array)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_array[i] = array[i];
		i++;
	}
	new_array[i] = str;
	new_array[i + 1] = NULL;
	return (new_array);
}

char	**make_envp(char **envp, t_state *s)
{
	char	**array;
	char	dir[PATH_MAX];
	char	*str;

	if (*envp)
		return (envp);
	array = ft_malloc(sizeof(char *), &(s->gc), s);
	if (!array)
		return (NULL);
	array[0] = NULL;
	if (getcwd(dir, PATH_MAX))
	{
		str = pft_strjoin("PWD=", dir, s);
		if (!str)
			return (NULL);
		array = append_char_star2(array, str, s);
		return (array);
	}
	return (NULL);
}

int	minishell(t_state *state, t_token ***array)
{
	char	*line;

	line = readline("minishell> ");
	if (!line)
	{
		destroy_gc(state->gc);
		exit(0);
	}
	if (!is_empty_line(line))
	{
		add_history(line);
		array = parseline(state, line);
		if (array)
		{
			set_parent_exec_sig();
			if (ft_make_exec(array, state) == EXIT_FAILURE)
				return (0);
		}
		if (state->exit_code == 128 + SIGQUIT)
			printf("Quit (core dumped)\n");
		else if (state->exit_code == 128 + SIGINT)
			printf("\n");
	}
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_token	***array;
	t_state	state;

	init_main(ac, av, &state);
	if (!state.gc)
		return (1);
	state.env = make_envp(envp, &state);
	if (!state.env)
		return (destroy_gc(state.gc), 1);
	array = ft_malloc(sizeof(t_token **), &state.gc, &state);
	if (!array)
		return (destroy_gc(state.gc), 0);
	while (1)
	{
		g_signal = 0;
		set_sig();
		if (minishell(&state, array) == EXIT_FAILURE)
			break ;
		shallow_clear(&(state.gc), state.env);
	}
	rl_clear_history();
	destroy_gc(state.gc);
	return (0);
}

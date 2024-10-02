/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_vars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theog <theog@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 20:45:15 by vispinos          #+#    #+#             */
/*   Updated: 2024/10/02 04:00:13 by theog            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../minishell.h" // decomment after code sync
#include "parsing.h"

int		is_regex(char c, int pos)
{
	if ((ft_isdigit(c) && pos > 0) || ft_isalpha(c) || c == '_')
		return (1);
	else
		return (0);
}

int get_var_len(char *str, int start)
{
	int	i;

	i = 0;
	while (str[i + start] && is_regex(str[i + start], i))
		i++;
	return (i);
}

static char *get_var_value(char *str, char **env)
{
	char	*value;
	int		i;

	value = NULL;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(str, env[i], ft_strlen(str)) == 0
			&& env[i][ft_strlen(str)] == '=')
		{
			if (value)
				free(value);
			value = ft_strdup(&(env[i][ft_strlen(str) + 1]));
		}
		i++;
	}
	return (value);
}

char	*replace_vars(char *str, t_state *s)
{
	int		i;
	int		i_save;
	int		sq;
	int		dq;
	int		next_var_len;
	int		cut;
	char 	*next_var_value;

	sq = 0;
	dq = 0;
	i = 0;
	while (str[i])
	{
		i_save = i;
		set_quotes_mode(&sq, &dq, str[i]);
		if (sq == 1 || str[i] != '$' || !str[i + 1]
			|| (!is_regex(str[i + 1], 0) && str[i + 1] != '?'))
			i++;
		else
		{
			if (str[i + 1] == '?')
			{
				next_var_value = ft_itoa(s->exit_code);
				cut = 2;
				i += ft_strlen(next_var_value) - cut;
			}
			else
			{
				next_var_len = get_var_len(str, i + 1);
				cut = next_var_len + 1;
				next_var_value = get_var_value(&str[i + 1], s->env);
				i += ft_strlen(next_var_value) - cut;
			}
			printf("next var value: %s\n", next_var_value);
			str = ft_join_all(str, next_var_value, i_save, cut);
			printf("str after join all: %s", str);
			if (!str)
				return (s->exit_code = 1, NULL);
		}
	}
	return (str);
}

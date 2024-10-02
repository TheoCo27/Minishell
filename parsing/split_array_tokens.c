/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_array_tokens.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vispinos <vispinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 23:41:06 by vispinos          #+#    #+#             */
/*   Updated: 2024/10/01 15:09:42 by vispinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../minishell.h" // decomment after code sync
#include "parsing.h"

static int	count_sub_arrays(t_token **token_array, int type)
{
	int	nb;
	int	mode;
	int	i;

	nb = 0;
	mode = 1;
	i = 0;
	while (i < array_len(token_array))
	{
		if (mode == 1)
		{
			if (token_array[i]->type != type)
			{
				mode = 0;
				nb++;
			}
		}
		else
		{
			if (token_array[i]->type == type)
				mode = 1;
		}
		i++;
	}
	return (nb);
}

/*
lap : len_array_param
*/
static t_token	**make_sub_array(t_token **token_array, int lap, int type, t_state *s)
{
	t_token		**sub_array;
	int			len;
	int			i;

	len = 0;
	while (len < lap && token_array[len]->type != type)
		len++;
	sub_array = malloc(sizeof(t_token *) * (len + 1));//ft_malloc(sizeof(t_token *) * (len + 1), &(s->gc));
	if (!sub_array)
		return (s->exit_code = 1, NULL);
	i = 0;
	while (i < len)
	{
		sub_array[i] = &(*(token_array[i]));
		i++;
	}
	sub_array[i] = NULL;
	return (sub_array);
}

/*
t_a : token_array
ita : index_token_array
ima : index_main_array
*/
t_token ***ft_split_array_tokens(t_token **t_a, int type, t_state *s)
{
	t_token	***array;
	int		ima;
	int		ita;

	array = malloc(sizeof(t_token **) * (count_sub_arrays(t_a, type) + 1));//ft_malloc(sizeof(t_token **) * (count_sub_arrays(t_a, type) + 1), &(s->gc));
	if (!array)
		return (s->exit_code = 1, NULL);
	ima = 0;
	ita = 0;
	while (ita < array_len(t_a))
	{
		while (ita < array_len(t_a) && (t_a[ita])->type == type)
			ita++;
		if (ita < array_len(t_a) && (t_a[ita])->type != type)
		{
			array[ima] = make_sub_array(&t_a[ita], (array_len(t_a) - ita), type, s);
			if (!array[ima])
				return (s->exit_code = 1, NULL);
			ita += array_len(array[ima]);
			ima++;
		}
	}
	array[ima] = NULL;
	return (array);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vispinos <vispinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 17:31:49 by vispinos          #+#    #+#             */
/*   Updated: 2024/10/01 17:02:16 by vispinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../minishell.h" // decomment after code sync
#include "parsing.h"

static int	noquote(int sq, int dq)
{
	if (sq == 0 && dq == 0)
		return (1);
	return (0);
}

static int	get_next_quote(char *line, int start, int quote)
{
	int	i;

	i = start;
	while (line[i])
	{
		if (line[i] == quote)
			return (i);
		i++;
	}
	return (-1);
}

int	find_word_len(char *line, int i)
{
	int	len;

	len = 0;
	while (line[i + len] && line[i + len] != SQUOTE && line[i + len] != DQUOTE
			&& line[i + len] != '<' && line[i + len] != '>' && line[i + len] != '|'
			&& !ft_is_space(line[i + len]))
		len++;
	return (len);
}

static t_token **make_token_array(char *line, t_token **token_array, t_state *s)
{
	int	i;
	int	sq;
	int	dq;
	int last_token_spe;
	int	next_quote;
	int	word_len;

	i = 0;
	sq = 0;
	dq = 0;
	last_token_spe = -1;
	while (line[i])
	{
		while (line[i] && (line[i] == ' ' || (line[i] >= 9 && line[i] <= 13)))
			i++;
		set_quotes_mode(&sq, &dq, line[i]);
		//printf("Iterating on line, i: %i, sq: %i, dq: %i\n", i, sq, dq);
		if (noquote(sq, dq))
		{
			while (line[i] && (line[i] == ' ' || (line[i] >= 9 && line[i] <= 13)))
				i++;
			if (line[i] == '<' && line[i + 1] == '<')
			{
				if (last_token_spe == 1)
					return (s->exit_code = 2, ft_putendl_fd("minishell: syntax error near unexpected token '<<'", 2), NULL);
				token_array = make_token_and_append(HEREDOC, NULL, token_array, s);
				i += 2;
				last_token_spe = 1;
			}
			else if (line[i] == '<')
			{
				if (last_token_spe == 1)
					return (s->exit_code = 2, ft_putendl_fd("minishell: syntax error near unexpected token '<'", 2), NULL);
				token_array = make_token_and_append(INFILE, NULL, token_array, s);
				i += 1;
				last_token_spe = 1;
			}
			else if (line[i] == '>' && line[i + 1] == '>')
			{
				if (last_token_spe == 1)
					return (s->exit_code = 2, ft_putendl_fd("minishell: syntax error near unexpected token '>>'", 2), NULL);
				token_array = make_token_and_append(OUTFILE_APPEND, NULL, token_array, s);
				i += 2;
				last_token_spe = 1;
			}
			else if (line[i] == '>')
			{
				if (last_token_spe == 1)
					return (s->exit_code = 2, ft_putendl_fd("minishell: syntax error near unexpected token 'newline'", 2), NULL);
				token_array = make_token_and_append(OUTFILE_TRUNCATE, NULL, token_array, s);
				i += 1;
				last_token_spe = 1;
			}
			else if (line[i] == '|')
			{
				if (last_token_spe == 1 || last_token_spe == -1)
					return (s->exit_code = 2, ft_putendl_fd("minishell: syntax error near unexpected token '|'", 2), NULL);
				token_array = make_token_and_append(PIPE, NULL, token_array, s);
				i += 1;
				last_token_spe = 1;
			}
			else
			{
				word_len = find_word_len(line, i);
				token_array = make_str_and_append_array(line, i, token_array, NOQUOTE_SEP, s);
				i += word_len;
				last_token_spe = 0;
			}
		}
		else if (sq == 1)
		{
			next_quote = get_next_quote(line, (i + 1), SQUOTE);
			if (next_quote == -1)
			{
				ft_putendl_fd("minishell: syntax error near unexpected token '", 2);
				return (s->exit_code = 2, NULL);
			}
			//printf("Next quote pos: %i\n", next_quote);
			token_array = make_str_and_append_array(line, i, token_array, SQUOTE, s);
			i = next_quote + 1;
			sq = 0;
			last_token_spe = 0;
		}
		else if (dq == 1)
		{
			next_quote = get_next_quote(line, (i + 1), DQUOTE);
			if (next_quote == -1)
			{
				ft_putendl_fd("minishell: syntax error near unexpected token \"", 2);
				return (s->exit_code = 2, NULL);
			}
			token_array = make_str_and_append_array(line, i, token_array, DQUOTE, s);
			i = next_quote + 1;
			dq = 0;
			last_token_spe = 0;
		}
		while (line[i] && (line[i] == ' ' || (line[i] >= 9 && line[i] <= 13)))
			i++;
	}
	return (token_array);
}

static int	last_array_elem_valid(t_token **array)
{
	int	type;
	int	spe;
	int	i;

	i = 0;
	type = -1;
	spe = -1;
	while (array[i])
	{
		type = array[i]->type;
		spe = array[i]->is_special;
		i++;
	}
	if (spe == 0)
		return (1);
	if (spe == 1 && type == PIPE)
		ft_putendl_fd("minishell: syntax error near unexpected token '|'", 2);
	else if (spe == 1)
		ft_putendl_fd("minishell: syntax error near unexpected token 'newline'", 2);
	return (0);
}

t_token	***parseline(t_state *s, char *line)
{
	t_token	**token_array;
	t_token	***main_array;

	//printf("Starting parseline()\n");
	line = replace_vars(line, s);
	if (!line)
		return (s->exit_code = 1, NULL);
	//printf("Line after parseline :\n%s\n", line);
	token_array = malloc(sizeof(t_token *));//ft_malloc(sizeof(t_token *), &(s->gc));
	if (!token_array)
		return (s->exit_code = 1, NULL);
	*token_array = NULL;
	//printf("Null token:\n");
	//print_token(*token_array);
	//printf("Starting to make array token\n");
	token_array = make_token_array(line, token_array, s);
	if (!token_array)
		return (s->exit_code = 1, NULL);
	//print_array(token_array);
	if (last_array_elem_valid(token_array) == 0)
		return (s->exit_code = 2, NULL);
	main_array = ft_split_array_tokens(token_array, PIPE, s);
	if (!main_array)
		return (s->exit_code = 1, NULL);
	return (main_array);
}

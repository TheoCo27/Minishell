/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_to_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcohen <tcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 04:41:59 by theog             #+#    #+#             */
/*   Updated: 2024/10/03 19:18:32 by tcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "../parsing/parsing.h"

static int ft_is_redir_token(t_token *token)
{
	if (token->type == INFILE)
		return (1);
	if (token->type == OUTFILE_APPEND)
		return (1);
	if (token->type == OUTFILE_TRUNCATE)
		return (1);
	if (token->type == HEREDOC)
		return (1);
	return (0);
}

t_info_exec *ft_convert_redir_token(t_info_exec *cmd, t_token **array, int *i)
{
	printf("in convert dir i = %d\n", *i);
    if (array[*i]->type == INFILE && array[(*i) + 1]->type == ARG)
    {
        cmd->infiles = ft_tabstr_addback(array[(*i) + 1]->content, cmd->infiles);
        if (!cmd->infiles)
            return (ft_pipelst_clear_node(cmd), NULL);
		printf("tab infiles : \n");
		ft_print_tabstr(cmd->infiles);
    }
    if (array[*i]->type == OUTFILE_APPEND && array[(*i) + 1]->type == ARG)
    {
        cmd->outfiles_app = ft_tabstr_addback(array[(*i) + 1]->content, cmd->outfiles_app);
        if (!cmd->infiles)
            return (ft_pipelst_clear_node(cmd), NULL);
		printf("tab outfiles app : \n");
		ft_print_tabstr(cmd->outfiles_app);
    }
    if (array[*i]->type == OUTFILE_TRUNCATE && array[(*i) + 1]->type == ARG)
    {
        cmd->outfiles_trunc = ft_tabstr_addback(array[(*i) + 1]->content, cmd->outfiles_trunc);
        if (!cmd->outfiles_trunc)
            return (ft_pipelst_clear_node(cmd), NULL);
		printf("tab outfiles trunc : \n");
		ft_print_tabstr(cmd->outfiles_trunc);
    }
	printf("before leaving convert dir i = %d\n", *i);
    return (cmd);
}

t_info_exec *ft_token_to_exec(t_token **array)
{
	t_info_exec *cmd;
	int			i;

	i = 0;
	cmd = ft_pipelst_new();
	if (!cmd)
		return (NULL);
	while(array[i])
	{
		printf("in token to exec i = %d\n", i);
		ft_convert_redir_token(cmd, array, &i);
		if (array[i]->type == CMD)
		{
			cmd->cmd = ft_strdup(array[i]->content);
			if (!cmd->cmd)
				return (ft_pipelst_clear_node(cmd), NULL);
			printf("cmd : %s", cmd->cmd);
		}
		if (i > 0 && array[i]->type == ARG && ft_is_redir_token(array[i - 1]) == 0)
		{
			cmd->arg = ft_tabstr_addback(array[i]->content, cmd->arg);
			if (!cmd->arg)
				return (ft_pipelst_clear_node(cmd), NULL);
			printf("tab arg : \n");
			ft_print_tabstr(cmd->arg);
		}
		i++;
	}
	return (cmd);
}

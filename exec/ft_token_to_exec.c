/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_to_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcohen <tcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 04:41:59 by theog             #+#    #+#             */
/*   Updated: 2024/10/02 19:48:18 by tcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "../parsing/parsing.h"

t_info_exec *ft_convert_redir_token(t_info_exec *cmd, t_token **array, int *i)
{
    if (array[*i]->type == INFILE && array[*i + 1]->type == ARG)
    {
        (*i)++;
        cmd->infiles = ft_tabstr_addback(array[*i]->content, cmd->infiles);
        if (!cmd->infiles)
            return (ft_pipelst_clear_node(cmd), NULL);
    }
    if (array[*i]->type == OUTFILE_APPEND && array[*i + 1]->type == ARG)
    {
        (*i)++;
        cmd->outfiles_app = ft_tabstr_addback(array[*i]->content, cmd->outfiles_app);
        if (!cmd->infiles)
            return (ft_pipelst_clear_node(cmd), NULL);
    }
    if (array[*i]->type == OUTFILE_TRUNCATE && array[*i + 1]->type == ARG)
    {
        (*i)++;
        cmd->outfiles_trunc = ft_tabstr_addback(array[*i]->content, cmd->outfiles_trunc);
        if (!cmd->outfiles_trunc)
            return (ft_pipelst_clear_node(cmd), NULL);
    }
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
		ft_convert_redir_token(cmd, array, &i);
		if (array[i]->type == CMD)
		{
			cmd->cmd = ft_strdup(array[i]->content);
			if (!cmd->cmd)
				return (ft_pipelst_clear_node(cmd), NULL);
		}
		if (array[i]->type == ARG)
		{
			cmd->arg = ft_tabstr_addback(array[i]->content, cmd->arg);
			if (!cmd->arg)
				return (ft_pipelst_clear_node(cmd), NULL);
			ft_print_tabstr(cmd->arg);
		}
		i++;
	}
	return (cmd);
}

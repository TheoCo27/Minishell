/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_while_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcohen <tcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 16:14:26 by theog             #+#    #+#             */
/*   Updated: 2024/10/26 17:13:10 by tcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_close_allpipes(t_info_exec *lst)
{
	t_info_exec	*cmd;

	cmd = lst;
	while (cmd)
	{
		close(cmd->pipe_fd[0]);
		close(cmd->pipe_fd[1]);
		cmd = cmd->next;
	}
	return (0);
}

int	ft_set_pipes(t_info_exec **lst)
{
	t_info_exec	*cmd;

	cmd = *lst;
	while (cmd)
	{
		if (ft_pipe(cmd->pipe_fd, lst, cmd) == -1)
			return (-1);
		cmd = cmd->next;
	}
	return (0);
}

int	ft_while_fork(t_info_exec **lst_cmd, char **env)
{
	t_info_exec	*cmd;
	t_info_exec	*last;

	cmd = *lst_cmd;
	last = ft_pipelst_last(cmd);
	while (cmd)
	{
		if (ft_fork(cmd, lst_cmd) == -1)
			return (-1);
		if (cmd->pid == 0 && cmd == *lst_cmd)
			ft_exec_child(cmd, lst_cmd, env, 0);
		if (cmd->pid == 0 && cmd == last)
			ft_exec_child(cmd, lst_cmd, env, 1);
		if (cmd->pid == 0)
			ft_exec_child(cmd, lst_cmd, env, 2);
		cmd = cmd->next;
	}
	return (0);
}

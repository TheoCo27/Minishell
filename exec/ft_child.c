/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcohen <tcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 16:02:22 by tcohen            #+#    #+#             */
/*   Updated: 2024/10/26 16:05:03 by tcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_close_wrongpipes(t_info_exec *cmd, t_info_exec **lst)
{
	t_info_exec	*next_cmd;
	t_info_exec	*prev_cmd;

	next_cmd = cmd->next;
	prev_cmd = cmd->prev;
	close(cmd->pipe_fd[0]);
	if (cmd == ft_pipelst_last(*lst))
		close(cmd->pipe_fd[1]);
	while (next_cmd)
	{
		ft_close_pipe(next_cmd->pipe_fd);
		next_cmd = next_cmd->next;
	}
	if (prev_cmd != NULL)
	{
		close(prev_cmd->pipe_fd[1]);
		prev_cmd = prev_cmd->prev;
	}
	while (prev_cmd)
	{
		ft_close_pipe(prev_cmd->pipe_fd);
		prev_cmd = prev_cmd->prev;
	}
	return (0);
}

int	ft_close_remaining_pipes(t_info_exec *cmd, t_info_exec **lst)
{
	t_info_exec	*last;

	last = ft_pipelst_last(*lst);
	if (cmd == *lst)
		close(cmd->pipe_fd[1]);
	else if (cmd == last)
		close(cmd->prev->pipe_fd[0]);
	else
	{
		close(cmd->pipe_fd[1]);
		close(cmd->prev->pipe_fd[0]);
	}
	return (0);
}

static int	nul_cmd_exit(t_info_exec *cmd, t_info_exec **lst)
{
	ft_close_remaining_pipes(cmd, lst);
	rl_clear_history();
	destroy_gc(cmd->state->gc);
	garbage_destroy();
	exit (0);
}

int	ft_exec_child(t_info_exec *cmd, t_info_exec **lst, char **env, int status)
{
	ft_close_wrongpipes(cmd, lst);
	if (status != 0)
		if (cmd->arg[0] != NULL && ft_dup2(cmd->prev->pipe_fd[0], 0) == -1)
			return (ft_close_remaining_pipes(cmd, lst), garbage_destroy(), 1);
	if (status != 1)
		if (cmd->arg[0] != NULL && ft_dup2(cmd->pipe_fd[1], 1) == -1)
			return (ft_close_remaining_pipes(cmd, lst), garbage_destroy(), 1);
	ft_redir_all(cmd, lst);
	if (cmd->arg[0] == NULL)
		nul_cmd_exit(cmd, lst);
	if (launch_if_builtin(cmd->arg, cmd->state) == 1)
	{
		status = cmd->state->exit_code;
		rl_clear_history();
		destroy_gc(cmd->state->gc);
		garbage_destroy();
		exit (status);
	}
	if (ft_path(env, cmd) == 1)
		return (ft_close_remaining_pipes(cmd, lst), garbage_destroy(), 1);
	ft_execve(cmd, lst);
	return (0);
}

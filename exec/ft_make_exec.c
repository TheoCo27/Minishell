/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcohen <tcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 16:44:50 by tcohen            #+#    #+#             */
/*   Updated: 2024/10/26 19:32:14 by tcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	one_out(t_info_exec *cmd, int status)
{
	rl_clear_history();
	destroy_gc(cmd->state->gc);
	garbage_destroy();
	exit (status);
}

int	checkif_onecmd(t_info_exec *cmd, t_state *state, t_info_exec **lst)
{
	int	status;
	int	nul_cmd;

	status = 0;
	nul_cmd = 0;
	if (cmd->arg[0] == NULL)
		nul_cmd = 1;
	if (ft_pipelst_size(cmd) == 1)
	{	
		if (nul_cmd == 0 && detect_builtin(cmd->arg[0]) != (-1))
		{
			if (launch_if_builtin(cmd->arg, cmd->state) == 1)
			{
				status = cmd->state->exit_code;
				if (ft_strcmp("exit", cmd->arg[0]) == 0)
					one_out(cmd, status);
				return (garbage_destroy(), status);
			}
		}
		status = ft_only_child(cmd, state->env, lst);
		return (status);
	}
	return (-80085);
}

static int	ft_get_out(t_info_exec *lst)
{
	int	status;

	status = 0;
	status = ft_wait_pids(lst, status);
	ft_destroy_heredocs(&lst);
	garbage_destroy();
	return (status);
}

static int	while_fork_failed(t_info_exec *lst)
{
	int	status;

	status = 0;
	status = ft_wait_pids(lst, status);
	ft_close_allpipes(lst);
	garbage_destroy();
	return (status);
}

// GOOOD FUNCTIION HERE
int	ft_make_exec(t_token ***cmd_array, t_state *state)
{
	t_info_exec	*lst;
	int			status;

	status = 0;
	lst = NULL;
	lst = ft_make_pipelst(cmd_array, state);
	if (!lst)
		return (1);
	if (ft_name_heredocs(&lst) == -1)
		return (garbage_destroy(), 1);
	if (ft_fill_all_heredocs(&lst) == -1)
		return (garbage_destroy(), 1);
	status = checkif_onecmd(lst, state, &lst);
	if (status != -80085)
		return (garbage_destroy(), status);
	if (ft_set_pipes(&lst) == -1)
		return (garbage_destroy(), 1);
	if (ft_while_fork(&lst, state->env) == -1)
		return (while_fork_failed(lst));
	if (ft_pipelst_size(lst) > 1)
		ft_close_allpipes(lst);
	status = ft_get_out(lst);
	return (status);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcohen <tcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 02:11:10 by theog             #+#    #+#             */
/*   Updated: 2024/10/06 17:51:10 by tcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "../parsing/parsing.h"

int	ft_only_child(t_info_exec *cmd, char **env, t_info_exec **lst)
{
    int status;

    status = 0;
    cmd->pid = fork();
    if (cmd->pid == 0)
    {
        // ft_cmd_arg(cmd->cmd, cmd, lst);
		ft_redir_all(cmd, lst);
        if (ft_path(env, cmd) == 1)
			return(ft_pipelst_clear(lst), 1);
	    ft_execve(cmd, lst);
    }
    status = ft_wait_pids(*lst, status);
    ft_pipelst_clear(lst);
	return (status);
}
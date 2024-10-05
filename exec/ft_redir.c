/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcohen <tcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 16:30:55 by tcohen            #+#    #+#             */
/*   Updated: 2024/10/05 16:56:43 by tcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_redir_infile(t_info_exec *cmd, t_info_exec **lst)
{
	int	i;

	i = 0;
	while(cmd->infiles[i])
	{
		cmd->in_fd = ft_open(cmd->infiles[i], 'r', cmd, lst);
		if (ft_dup2(cmd->in_fd, 0) == -1)
		{
			close(cmd->in_fd);
			ft_close_pipe(cmd->pipe_fd);//I think just close pipd_fd[1]
			ft_close_remaining_pipes(cmd, lst);
			ft_pipelst_clear(lst);
			exit(errno);
		}
		i++;
	}
	return (0);
}

static int	ft_redir_outfiles_trunc(t_info_exec *cmd, t_info_exec **lst)
{
	int	i;

	i = 0;
	while(cmd->outfiles_trunc[i])
	{
		cmd->out_fd = ft_open(cmd->outfiles_trunc[i], 'w', cmd, lst);
		if (ft_dup2(cmd->in_fd, 1) == -1)
		{
			close(cmd->in_fd);
			ft_close_pipe(cmd->pipe_fd);//I think just close pipd_fd[1]
			ft_close_remaining_pipes(cmd, lst);
			ft_pipelst_clear(lst);
			exit(errno);
		}
	}
	return (0);
}

static int	ft_redir_outfiles_app(t_info_exec *cmd, t_info_exec **lst)
{
	int	i;

	i = 0;
	while(cmd->outfiles_app[i])
	{
		cmd->out_fd = ft_open(cmd->outfiles_app[i], 'a', cmd, lst);
		if (ft_dup2(cmd->in_fd, 1) == -1)
		{
			close(cmd->in_fd);
			ft_close_pipe(cmd->pipe_fd);//I think just close pipd_fd[1]
			ft_close_remaining_pipes(cmd, lst);
			ft_pipelst_clear(lst);
			exit(errno);
		}
		i++;
	}
	return (0);
}

int ft_redir_all(t_info_exec *cmd, t_info_exec **lst)
{
	ft_redir_infile(cmd, lst);
	ft_redir_outfiles_app(cmd, lst);
	ft_redir_outfiles_trunc(cmd, lst);
	return (0);
}

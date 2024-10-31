/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcohen <tcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:59:29 by tcohen            #+#    #+#             */
/*   Updated: 2024/10/26 16:29:08 by tcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "../signal/ft_signal.h"

static void	fill_h_init(char *line, size_t *limiter_len, t_file_lst *file)
{
	line = NULL;
	*limiter_len = ft_strlen(file->delimiter);
	set_heredoc_sig();
	in_heredoc(1);
	(void)line;
}

int	ft_fill_heredoc(t_file_lst *file, char *line, size_t limiter_len)
{
	fill_h_init(line, &limiter_len, file);
	while (1)
	{
		line = readline("heredoc> ");
		if (!line || g_signal != 0)
		{
			if (g_signal != 0)
				return (in_heredoc(-1), -1);
			error_ctrl_d(file->delimiter);
			break ;
		}
		if (ft_strncmp(line, file->delimiter, limiter_len) == 0)
		{
			g_free(line);
			break ;
		}
		file->heredoc_content = ft_tabstr_addback(line, file->heredoc_content);
		if (!file->heredoc_content)
			return (g_free(line), -1);
		g_free(line);
	}
	in_heredoc(-1);
	set_parent_exec_sig();
	return (0);
}

int	ft_fill_all_heredocs(t_info_exec **lst)
{
	t_info_exec	*cmd;
	t_file_lst	*file;
	char		*line;
	size_t		limiter_len;

	cmd = *lst;
	line = NULL;
	limiter_len = 0;
	while (cmd)
	{
		file = cmd->file_lst;
		while (file)
		{
			if (file->type == 'h')
			{
				if (ft_fill_heredoc(file, line, limiter_len) == -1)
					return (-1);
			}
			file = file->next;
		}
		cmd = cmd->next;
	}
	return (0);
}

int	ft_destroy_heredocs(t_info_exec **lst)
{
	t_info_exec	*cmd;
	t_file_lst	*file;

	cmd = *lst;
	while (cmd)
	{
		file = cmd->file_lst;
		while (file)
		{
			if (file->type == 'h')
			{
				unlink(file->name);
			}
			file = file->next;
		}
		cmd = cmd->next;
	}
	return (0);
}

t_heredoc	*ft_make_heredoc(t_info_exec *cmd, t_info_exec **lst)
{
	t_heredoc	*h;

	h = g_malloc(sizeof(t_heredoc) * 1);
	if (!h)
		return (NULL);
	h->heredoc_name = ft_strdup("heredoc");
	if (!h->heredoc_name)
		return (NULL);
	h->heredoc_name = ft_anti_fuck_heredoc(h->heredoc_name);
	if (!h->heredoc_name)
		return (NULL);
	h->fd_heredoc = ft_open(h->heredoc_name, 'h', cmd, lst);
	return (h);
}

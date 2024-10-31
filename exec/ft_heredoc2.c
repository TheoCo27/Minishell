/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcohen <tcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 16:06:40 by tcohen            #+#    #+#             */
/*   Updated: 2024/10/26 16:26:06 by tcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "../signal/ft_signal.h"

char	*ft_anti_fuck_heredoc(char *file_name)
{
	while (access(file_name, F_OK) == 0)
	{
		file_name = ft_str_free_s1_join(file_name, "1");
		if (!file_name)
			return (g_free(file_name), NULL);
	}
	return (file_name);
}

static char	*name_helper(char *name, t_file_lst *file)
{
	name = ft_str_free_s1_join(name, "1");
	if (!name)
		return (NULL);
	name = ft_anti_fuck_heredoc(name);
	if (!name)
		return (NULL);
	file->name = ft_strdup(name);
	if (!file->name)
		return (NULL);
	return (name);
}

int	ft_name_heredocs(t_info_exec **lst)
{
	t_info_exec	*cmd;
	t_file_lst	*file;
	char		*name;

	cmd = *lst;
	name = ft_strdup(".heredoc");
	if (!name)
		return (-1);
	while (cmd)
	{
		file = cmd->file_lst;
		while (file)
		{
			if (file->type == 'h')
				if (name_helper(name, file) == NULL)
					return (-1);
			file = file->next;
		}
		cmd = cmd->next;
	}
	return (0);
}

void	error_ctrl_d(char *file_delimiter)
{
	ft_putstr_fd("warning: here-document delimited", 2);
	ft_putstr_fd(" by end-of-file (wanted '", 2);
	ft_putstr_fd(file_delimiter, 2);
	ft_putstr_fd("')\n", 2);
}

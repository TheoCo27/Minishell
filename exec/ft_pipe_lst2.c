/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_lst2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcohen <tcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 16:58:27 by tcohen            #+#    #+#             */
/*   Updated: 2024/10/26 17:01:04 by tcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_info_exec	*ft_pipelst_new(void)
{
	t_info_exec	*new;

	new = (t_info_exec *)g_malloc(sizeof(t_info_exec));
	if (!new)
		return (NULL);
	ft_bzero(new, sizeof(t_info_exec));
	new->cmd = NULL;
	new->next = NULL;
	new->prev = NULL;
	new->pid = -1;
	new->file_lst = NULL;
	new->arg = ft_make_tabstr();
	if (!new->arg)
		return (g_free(new), NULL);
	return (new);
}

t_info_exec	*ft_pipelst_last(t_info_exec *lst)
{
	t_info_exec	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
	return (tmp);
}

void	ft_pipelst_addback(t_info_exec **lst, t_info_exec *new)
{
	t_info_exec	*last;

	if (!lst || !*lst)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	last = ft_pipelst_last(*lst);
	last->next = new;
	new->prev = last;
}

void	ft_pipelst_clear_node(t_info_exec *node)
{
	if (node->cmd)
		g_free(node->cmd);
	if (node->arg)
		ft_free_all(node->arg);
	if (node->file_lst)
		ft_filelstclear(&node->file_lst);
	g_free(node);
}

void	ft_pipelst_clear(t_info_exec **lst)
{
	t_info_exec	*temp;

	if (!lst)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		if ((*lst)->cmd)
			g_free((*lst)->cmd);
		if ((*lst)->arg)
			ft_free_all((*lst)->arg);
		if ((*lst)->file_lst)
			ft_filelstclear(&(*lst)->file_lst);
		*lst = temp;
	}
	*lst = NULL;
}

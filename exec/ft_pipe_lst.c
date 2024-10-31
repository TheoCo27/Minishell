/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcohen <tcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 19:09:56 by tcohen            #+#    #+#             */
/*   Updated: 2024/10/26 17:00:21 by tcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_pipelst_printcmd(t_info_exec	**lst)
{
	t_info_exec	*temp;
	int			count;

	temp = *lst;
	count = 1;
	while (temp)
	{
		ft_putendl_fd("Commmand :", 1);
		if (temp->cmd)
			ft_putendl_fd(temp->cmd, 1);
		if (!temp->cmd)
			ft_putendl_fd("cmd NULL", 1);
		ft_putendl_fd("Arg :", 1);
		ft_print_tabstr(temp->arg);
		ft_print_filelst(&temp->file_lst);
		temp = temp->next;
		count++;
	}
}

void	ft_pipelst_reverse_printcmd(t_info_exec	**lst)
{
	t_info_exec	*temp;
	int			count;

	temp = *lst;
	temp = ft_pipelst_last(temp);
	count = 1;
	while (temp)
	{
		ft_putnbr_fd(count, 1);
		ft_putstr_fd(" .", 1);
		ft_putendl_fd(temp->cmd, 1);
		temp = temp->prev;
		count++;
	}
}

t_info_exec	*ft_make_pipelst(t_token ***array, t_state *state)
{
	size_t		i;
	t_info_exec	*lst;
	t_info_exec	*new;

	i = 0;
	lst = NULL;
	while (array[i])
	{
		new = ft_token_to_exec(array[i]);
		if (!new)
			return (garbage_destroy(), NULL);
		new->state = state;
		ft_pipelst_addback(&lst, new);
		i++;
	}
	return (lst);
}

size_t	ft_pipelst_size(t_info_exec *lst)
{
	t_info_exec	*temp;
	size_t		lst_size;

	temp = lst;
	lst_size = 0;
	while (temp)
	{
		temp->index = lst_size;
		lst_size++;
		temp = temp->next;
	}
	return (lst_size);
}

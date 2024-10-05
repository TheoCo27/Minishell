/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcohen <tcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 19:09:56 by tcohen            #+#    #+#             */
/*   Updated: 2024/10/05 14:38:55 by tcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "../parsing/parsing.h"

t_info_exec	*ft_pipelst_new(void)
{
	t_info_exec	*new;

	new = (t_info_exec *)malloc(sizeof(t_info_exec));
	if (!new)
		return (NULL);
	ft_bzero(new, sizeof(t_info_exec));
	new->cmd = NULL;
	new->next = NULL;
	new->prev = NULL;
	new->pid = -1;
	new->i_heredoc = -1;
	new->infiles = ft_make_tabstr();
	if (!new->infiles)
		return (free(new), NULL);
	new->outfiles_trunc = ft_make_tabstr();
	if (!new->outfiles_trunc)
		return (ft_free_all(new->infiles), free(new), NULL);
	new->outfiles_app = ft_make_tabstr();
	if (!new->outfiles_app)
		return (ft_free_all(new->outfiles_trunc), ft_free_all(new->infiles), free(new), NULL);
	new->arg = ft_make_tabstr();
	if (!new->arg)
		return (ft_free_all(new->outfiles_app), ft_free_all(new->outfiles_trunc), 
			ft_free_all(new->infiles), free(new), NULL);
	return (new);
}

// t_info_exec	*ft_pipelst_new(void)
// {
// 	t_info_exec	*new;

// 	new = (t_info_exec *)malloc(sizeof(t_info_exec));
// 	if (!new)
// 		return (NULL);
// 	ft_bzero(new, sizeof(t_info_exec));
// 	new->cmd = NULL;
// 	new->next = NULL;
// 	new->prev = NULL;
// 	new->pid = -1;
// 	return (new);
// }

t_info_exec	*ft_pipelst_last(t_info_exec *lst)
{
	t_info_exec	*tmp;

	tmp = lst;
	while(tmp)
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
		free(node->cmd);
	if (node->arg)
		ft_free_all(node->arg);
	if (node->infiles)
		ft_free_all((node)->infiles);
	if (node->outfiles_trunc)
		ft_free_all((node)->outfiles_trunc);
	if (node->outfiles_app)
	ft_free_all((node)->outfiles_app);
	free(node);
}

void	ft_pipelst_clear(t_info_exec **lst)
{
	t_info_exec	*temp;

	if (!lst)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		//ici free le contenue du node;
		if ((*lst)->cmd)
			free((*lst)->cmd);
		if ((*lst)->arg)
			ft_free_all((*lst)->arg);
		if ((*lst)->infiles)
			ft_free_all((*lst)->infiles);
		if ((*lst)->outfiles_trunc)
			ft_free_all((*lst)->outfiles_trunc);
		if ((*lst)->outfiles_app)
		ft_free_all((*lst)->outfiles_app);
		*lst = temp;
	}
	*lst = NULL;
}

void	ft_pipelst_printcmd(t_info_exec	**lst)
{
	t_info_exec	*temp;
	int			count;

	temp = *lst;
	count = 1;
	while(temp)
	{
		ft_putendl_fd("Commmand :", 1);
		if (temp->cmd)
			ft_putendl_fd(temp->cmd, 1);
		if (!temp->cmd)
			ft_putendl_fd("cmd NULL", 1);
		ft_putendl_fd("Arg :", 1);
		ft_print_tabstr(temp->arg);
		ft_putendl_fd("Infiles :", 1);
		ft_print_tabstr(temp->infiles);
		ft_putendl_fd("Outfiles App:", 1);
		ft_print_tabstr(temp->outfiles_app);
		ft_putendl_fd("Outfiles Trunc:", 1);
		ft_print_tabstr(temp->outfiles_trunc);
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
	while(temp)
	{
		ft_putnbr_fd(count, 1);
		ft_putstr_fd(" .", 1);
		ft_putendl_fd(temp->cmd, 1);
		temp = temp->prev;
		count++;
	}
}


t_info_exec	*ft_make_pipelst(t_token ***array)
{
	size_t		i;
	t_info_exec	*lst;
	t_info_exec	*new;

	i = 0;
	lst = NULL;
	while(array[i])
	{
		new = ft_token_to_exec(array[i]);
		if (!new)
			return (ft_pipelst_clear(&lst), NULL);
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
	while(temp)
	{
		temp->index = lst_size;
		lst_size++;
		temp = temp->next;
	}
	return(lst_size);
}

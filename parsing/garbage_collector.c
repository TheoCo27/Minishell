/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vispinos <vispinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:45:34 by vispinos          #+#    #+#             */
/*   Updated: 2024/10/01 15:55:42 by vispinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../minishell.h" // decomment after code sync
#include "parsing.h"

t_list	*ft_lstnew(void *content)
{
	struct s_list	*list;

	list = malloc(sizeof(struct s_list));
	if (!list)
		return (NULL);
	list->content = content;
	return (list);
}

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	struct s_list	*ptr;

	ptr = *alst;
	if (!ptr)
	{
		*alst = new;
		return ;
	}
	while (ptr->next != NULL)
	{
		ptr = ptr->next;
	}
	ptr->next = new;
}

void	*ft_malloc(size_t size, t_list *gc)
{
	void	*space;

	space = malloc(size);
	if (!space)
		return (NULL);
	if (!gc)
		*gc = *ft_lstnew(space);
	else
		ft_lstadd_back(&gc, space);
	return (space);
}

void	destroy_gc(t_list *gc)
{
	t_list	*temp;

	while (gc)
	{
		temp = (gc)->next;
		if ((gc)->content)
			free((gc)->content);
		free(gc);
		gc = temp;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabstrprint.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcohen <tcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 14:55:05 by tcohen            #+#    #+#             */
/*   Updated: 2024/10/26 15:03:52 by tcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_tabstr(char **tabstr)
{
	char	**temp;

	temp = tabstr;
	if (temp == NULL || *temp == NULL)
		return ;
	while (*temp)
	{
		ft_putendl_fd(*temp, 1);
		temp++;
	}
}

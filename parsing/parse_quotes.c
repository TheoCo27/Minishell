/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vispinos <vispinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 17:40:05 by vispinos          #+#    #+#             */
/*   Updated: 2024/09/30 20:42:05 by vispinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../minishell.h" // decomment after code sync
#include "parsing.h"

void	set_quotes_mode(int *sq, int *dq, char c)
{
	if (c == SQUOTE && *sq == 0 && *dq == 0)
		*sq = 1;
	else if (c == DQUOTE && *sq == 0 && *dq == 0)
		*dq = 1;
	else if (c == SQUOTE && *sq == 1)
		*sq = 0;
	else if (c == DQUOTE && *dq == 1)
		*dq = 0;
}

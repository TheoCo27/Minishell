/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcohen <tcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 18:12:57 by tcohen            #+#    #+#             */
/*   Updated: 2024/10/26 18:05:54 by tcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SIGNAL_H
# define FT_SIGNAL_H

# include "../minishell.h"
# include "../exec/pipex.h"
# include <signal.h>

void	set_sig(void);
void	set_heredoc_sig(void);
void	set_exec_sig(void);
int		sig_event(void);
void	set_parent_exec_sig(void);

#endif
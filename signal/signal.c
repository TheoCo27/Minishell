/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcohen <tcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 20:12:07 by tcohen            #+#    #+#             */
/*   Updated: 2024/10/26 15:44:54 by tcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_signal.h"
#include <readline/readline.h>
#include <readline/history.h>

static void	sig_handler(int sig)
{
	g_signal = 128 + sig;
	if (sig == SIGINT)
		get_state(NULL)->exit_code = 128 + SIGINT;
	if (g_signal == 128 + SIGINT)
	{
		rl_replace_line("", 0);
		rl_done = 1;
	}
}

void	set_sig(void)
{
	rl_event_hook = sig_event;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

static void	heredoc_sig_handler(int sig)
{
	g_signal = 128 + sig;
	get_state(NULL)->exit_code = 128 + sig;
	rl_done = 1;
}

void	set_heredoc_sig(void)
{
	rl_event_hook = sig_event;
	signal(SIGINT, heredoc_sig_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

void	set_exec_sig(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_IGN);
}

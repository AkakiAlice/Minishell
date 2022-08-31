/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmitsuko <pmitsuko@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 07:05:49 by pmitsuko          #+#    #+#             */
/*   Updated: 2022/08/31 07:36:28 by pmitsuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	SIG_HANDLE_MINISHELL
**	------------
**	DESCRIPTION
**	Handles signals from minishell.
**	PARAMETERS
**	#1. The signal (signum);
**	RETURN VALUES
**	-
*/
void	sig_handle_minishell(int signum)
{
	write(1, "\n", 1);
	g_data.status = 130;
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	(void)signum;
}

/*	SIG_HANDLE_EXEC_PARENT
**	------------
**	DESCRIPTION
**	Handles signals from parent process.
**	PARAMETERS
**	#1. The signal (signum);
**	RETURN VALUES
**	-
*/
void	sig_handle_exec_parent(int signum)
{
	if (signum == 2)
		g_data.status = 130;
	if (signum == 3)
	{
		g_data.status = 131;
		write(1, "Quit", 4);
	}
	write(1, "\n", 1);
}

/*	SIG_HANDLE_HEREDOC_CHILD
**	------------
**	DESCRIPTION
**	Handles signals from heredoc child process.
**	PARAMETERS
**	#1. The signal (signum);
**	RETURN VALUES
**	-
*/
void	sig_handle_heredoc_child(int signal)
{
	write(1, "\n", 1);
	clear_minishell();
	exit(130);
	(void) signal;
}

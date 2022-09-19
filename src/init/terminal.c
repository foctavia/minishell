/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 13:57:12 by owalsh            #+#    #+#             */
/*   Updated: 2022/09/19 19:01:46 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    sig_exit(int signum)
{
    (void)signum;
    write(2, "exit\n", 5);
    exit(0);
}

void    sig_nl(int signum)
{
    (void)signum;
	printf("\n");
	g_global.data->shell.input = readline(SUCESS_PROMPT);
}

void	init_terminal(void)
{
	struct termios 	dflt;
	struct termios 	new;

	dflt = g_global.data->terminal.dftl;
	new = g_global.data->terminal.new;
	if (tcgetattr(0, &dflt) == -1)
		perror("terminal");
	memcpy(&new, &dflt, sizeof(struct termios));
	new.c_cc[VINTR] = 3;
	new.c_cc[VQUIT] = 0;
	new.c_cc[VEOF] = 34;
    signal(SIGINT, &sig_exit);
	// signal(SIGQUIT, &sig_exit);
	tcsetattr(0, TCSANOW, &new);
	// get attribute to set as default -> to put back default ermios at the end 
	// change attributes as required
	// manage signals
}

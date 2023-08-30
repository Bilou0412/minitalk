/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 17:34:59 by bmoudach          #+#    #+#             */
/*   Updated: 2023/08/25 21:37:26by bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"
#include <signal.h>

static void	sigint_handler(int sig, siginfo_t *info, void *context)
{
	int			tab[8];
	static int	i;
	static int	c;
	pid_t client_pid;

	client_pid = info->si_pid;
	(void)context;
	tab[0] = 1;
	tab[1] = 2;
	tab[2] = 4;
	tab[3] = 8;
	tab[4] = 16;
	tab[5] = 32;
	tab[6] = 64;
	tab[7] = 128;
	if ((i <= 7) && (sig == SIGUSR2))
	{
		c = c + tab[i];
		i++;
		usleep(50);
		kill(client_pid, SIGUSR1);
		
	}
	else if (sig == SIGUSR1)
	{
		i++;
		usleep(50);
		kill(client_pid, SIGUSR1);
	}
	if (i == 8)
	{
		i = 0;
		ft_putchar_fd(c, 1);
		c = 0;
	}
}

int	main(void)
{
	pid_t serv_pid;
	struct sigaction act;

	serv_pid = 0;
	serv_pid = getpgid(serv_pid);
	ft_printf("%d\n", serv_pid);
	act.sa_sigaction = sigint_handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;
	while (1)
	{
		sigaction(SIGUSR1, &act, 0);
		sigaction(SIGUSR2, &act, 0);
		pause();
	}
	return (0);
}
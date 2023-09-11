/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 20:11:35 by bmoudach          #+#    #+#             */
/*   Updated: 2023/09/11 22:49:14y bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"
#include <signal.h>

static void	sigint_handler(int sig, siginfo_t *info, void *context)
{
	static int	tab[8] = {1, 2, 4, 8, 16, 32, 64, 128};
	static int	i;
	static int	c;
	pid_t		client_pid;

	client_pid = info->si_pid;
	(void)context;
	if ((i <= 7) && (sig == SIGUSR2))
	{
		c = c + tab[i];
		i++;
	}
	else if (sig == SIGUSR1)
		i++;
	if (i == 8)
	{
		i = 0;
		if (c == 0)
		{
			kill(client_pid, SIGUSR1);
			return ;
		}
		ft_putchar_fd(c, 1);
		c = 0;
	}
}
void	close_exit(int sig)
{
	if (sig)
		exit(0);
}

int	main(void)
{
	pid_t serv_pid;
	struct sigaction act;

	serv_pid = 0;
	serv_pid = getpgid(serv_pid);
	ft_printf("%d\n", serv_pid);
	act.sa_sigaction = sigint_handler;
	act.sa_flags = SA_SIGINFO;
	while (1)
	{
		sigaction(SIGUSR1, &act, 0);
		sigaction(SIGUSR2, &act, 0);
		pause();
	}
	return (0);
}
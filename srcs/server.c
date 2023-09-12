/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 20:20:31 by bmoudach          #+#    #+#             */
/*   Updated: 2023/09/12 21:25:53 by bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

pid_t	g_serv_pid;

static void	sigint_handler(int sig, siginfo_t *info, void *context)
{
	static int	tab[8] = {1, 2, 4, 8, 16, 32, 64, 128};
	static int	i;
	static int	c;
	pid_t		client_pid;

	client_pid = info->si_pid;
	(void)context;
	if ((i <= 7) && (sig == SIGUSR2))
		c = c + tab[i];
	i++;
	if (i == 8)
	{
		i = 0;
		if (c == 0)
		{
			kill(client_pid, SIGUSR1);
			ft_printf("\n\n\033[34;01mPID :\033[00m %d\n", g_serv_pid);
			return ;
		}
		ft_putchar_fd(c, 1);
		c = 0;
	}
	kill(client_pid, SIGUSR2);
}

void	close_exit(int sig)
{
	if (sig)
		exit(0);
}

int	main(void)
{
	struct sigaction	act;

	sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask, SIGINT);
	g_serv_pid = getpgid(g_serv_pid);
	ft_printf("\033[34;01mPID :\033[00m %d\n\n", g_serv_pid);
	act.sa_sigaction = sigint_handler;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &act, 0);
	sigaction(SIGUSR2, &act, 0);
	signal(SIGINT, &close_exit);
	while (1)
		usleep(10);
	return (0);
}

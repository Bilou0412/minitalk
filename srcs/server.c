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

static void	sigint_handler(int sig)
{
	static int			tab[8] = {1,2,4,8,16,32,64,128};
	static int	i;
	static int	c;

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
		ft_putchar_fd(c, 1);
		c = 0;
	}
}
void close_exit(int sig)
{
	if(sig)
		exit(0);
}

int	main(void)
{
	pid_t serv_pid;

	serv_pid = 0;
	serv_pid = getpgid(serv_pid);
	ft_printf("%d\n", serv_pid);
	while (1)
	{
		signal(SIGUSR1, &sigint_handler);
		signal(SIGUSR2, &sigint_handler);
		signal(SIGINT,&close_exit);
		pause();
	}
	return (0);
}
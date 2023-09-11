/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 20:11:17 by bmoudach          #+#    #+#             */
/*   Updated: 2023/09/11 21:47:49y bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

void	send_info(t_client info_client)
{
	static int	i;
	static int	bit_to_send;

	bit_to_send = 0;
	i = 0;
	while (info_client.msg[i])
	{
		while (bit_to_send <= 7)
		{
			if ((info_client.msg[i] >> bit_to_send) & 1)
				kill(info_client.serv_pid, SIGUSR2);
			else
				kill(info_client.serv_pid, SIGUSR1);
			bit_to_send++;
			usleep(500);
		}
		bit_to_send = 0;
		i++;
	}
	bit_to_send = 0;
	while(bit_to_send <= 7)
	{
		kill(info_client.serv_pid, SIGUSR1);
		bit_to_send++;
		usleep(500);
	}
}

static void	action(int sig)
{
	if (sig)
	{
		ft_putstr("\033[32;01mMessage bien recu\033[00m\n");
		exit(0);
		return ;
	}
}

int	main(int argc, char *argv[])
{
	t_client info_client;
	
	if (argc != 3)
		return (0);
	info_client.serv_pid = ft_atoi(argv[1]);
	info_client.msg = argv[2];
	signal(SIGUSR1, &action);
	send_info(info_client);
	while(1)
		pause();
	return(0);
}
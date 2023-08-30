/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 17:35:02 by bmoudach          #+#    #+#             */
/*   Updated: 2023/08/28 14:50:30ach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

t_client	info_client;

void	send_info(int sig)
{
	static int	i;
	static int	bit_to_send;

	if(sig == 0)
		return ;
	bit_to_send = 0;
	i = 0;
	if (info_client.msg[i])
	{
		if (bit_to_send <= 7)
		{
			if ((info_client.msg[i] >> bit_to_send) & 1)
				kill(info_client.serv_pid, SIGUSR2);
			else
				kill(info_client.serv_pid, SIGUSR1);
			bit_to_send++;
		}
		bit_to_send = 0;
		i++;
	}
}

int	main(int argc, char *argv[])
{
	if (argc != 3)
		return (0);
	info_client.serv_pid = ft_atoi(argv[1]);
	info_client.msg = argv[2];
	send_info(1);
	while (1)
	{
		signal(SIGUSR1, send_info);
		pause();
	}
	return(0);
}
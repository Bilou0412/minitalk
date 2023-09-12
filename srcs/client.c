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
}

int	main(int argc, char *argv[])
{
	t_client info_client;
	if (argc != 3)
		return (0);
	info_client.serv_pid = ft_atoi(argv[1]);
	info_client.msg = argv[2];
	send_info(info_client);
	return (0);
}
#ifndef MINITALK_H
# define MINITALK_H

# include "../libft/libft.h"
# include <signal.h>
# include <sys/types.h>

typedef struct s_client
{
	pid_t	serv_pid;
	char	*msg;
}			t_client;

#endif
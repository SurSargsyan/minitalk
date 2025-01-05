/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 22:12:44 by marvin            #+#    #+#             */
/*   Updated: 2025/01/03 22:12:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_mini  *serber_initiate(void)
{
    t_mini  *talk;

    talk = malloc(sizeof(t_mini));
    if (!talk)
    {
        ft_putstr("ERROR!, malloc failed :(!\n)");
        exit(EXIT_FAILURE);
    }
    talk->pid_server = 0;
    talk->pid_client = 0;
    return (talk);
}

void    server_recieve(int boolean)
{
    static int      bit_displacement = 0;
    static char     letter = 0;

    letter += ((boolean & 1) << bit_displacement++);
    if (bit_displacement == 7)
    {
        write(1, &letter, 1);
        if (!letter)
            write(1, "\n", 1);
        bit_displacement = 0;
        letter = 0;
    }
    return ;
}

void    server_loop(t_mini *talk)
{
    while (1)
    {
        if ((signal(SIGUSR1, server_recieve) == SIG_ERR) 
            || (signal(SIGUSR2, server_recieve) == SIG_ERR))
            {
                ft_putstr("ERROR!, Signal error x_x!\n");
                free(talk);
                exit(EXIT_FAILURE);
            }
            _sleep(2);
    }
    return ;
}
int	main(int nword, char *arguments[])
{
	t_mini	*talk;
	
	(void)arguments;
	talk = NULL;
	if (nword != 1)
	{
		ft_putstr("ERROR!, Use \"./server\" with 1 argument please :)\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		talk = server_initiate();
		talk->pid_server = getpid();
		ft_putstr("SUCCESS!, Server is ready :D! The PID: ");
		ft_putnbr(talk->pid_server);
		write(1, "\n", 1);
		server_loop(talk);
	}
	free(talk);
	return (EXIT_SUCCESS);
}
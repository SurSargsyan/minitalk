/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 22:26:27 by marvin            #+#    #+#             */
/*   Updated: 2025/01/03 22:26:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_mini  *client_initiate(void)
{
    t_mini  *talk;

    talk = malloc(sizeof(t_mini));
    if (!talk)
    {
        ft_putstr("ERROR!, malloc failed :( !\n");
        exit(EXIT_FAILURE);
    }
    talk->pid_server = 0;
    talk->pid_client = 0;
    return (talk);
}
void    client_send(t_mini *talk, char *message)
{
    int bit_desplacement;
    int i;
    int signal;

    i = -1;
    while (++i <= ft_strlen(message))
    {
        bit_desplacement = -1;
        signal = 0;
        while (++bit_desplacement < 7)
        {
            if ((message[i] >> bit_desplacement) & 1)
            {
                signal = SIGUSR2;
            }
            else
                signal = SIGUSR1;
            kill(talk->pid_server, signal);
            usleep(200);
        }
    }
    return ;
}
int	main(int nword, char *arguments[])
{
	t_mini	*talk;

	talk = NULL;
	if (nword != 3)
	{
		ft_putstr("ERROR!, Use \"./server\" with 3 argument please :)\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		talk = client_initiate();
		talk->pid_server = ft_atoi(arguments[1]);
		if (talk->pid_server <= 0)
		{
			ft_putstr("ERROR!, PID is equal or less than 0 x-x!\n");
			free(talk);
			exit(EXIT_FAILURE);
		}
		client_send(talk, arguments[2]);
	}
	free(talk);
	return (EXIT_SUCCESS);
}
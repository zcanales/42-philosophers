/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 10:53:55 by zcanales          #+#    #+#             */
/*   Updated: 2021/12/17 16:11:05 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"
#include <stdlib.h>
#include <stdio.h>

int	msg_error(t_param *ap, char *str, int err)
{
	if (str)
		printf("%s", str);
	if (ap != NULL)
	{
		if (ap->th != NULL)
			free(ap->th);
		if (ap->pid != NULL)
			free(ap->pid);
		free(ap);
	}
	return (err);
}

int	main(int argc, char **argv)
{
	t_param		*ap;

	if (init_to_null(&ap))
		return (1);
	if (argc != 6 && argc != 5)
		return (msg_error
			(ap, "Usage:[./a.out][nbr][t_die][t_eat][t_sleep][t_times]\n", 1));
	if (init_ap(ap, argc, argv))
		return (msg_error(ap, "Could not init structures\n", 1));
	if (create_process(ap))
		return (msg_error(ap, "Thread problems\n", 1));
	return (msg_error(ap, "", 0));
}

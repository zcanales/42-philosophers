/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 13:55:44 by zcanales          #+#    #+#             */
/*   Updated: 2021/12/15 19:11:49 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <string.h>
#include <stdlib.h>

int	init_philo(t_philo *philo, int i, t_param *ap)
{
	memset(philo, 0, sizeof(t_philo));
	philo->index = i;
	if (!(philo->index == (ap->nbr - 1)))
		philo->next = i + 1;
	philo->ap = ap;
	return (0);
}

int	init_mutex(t_param *ap)
{
	int	i;

	ap->mutex_fork = malloc(sizeof(pthread_mutex_t) * ap->nbr);
	memset(ap->mutex_fork, 0, sizeof(pthread_mutex_t) * ap->nbr);
	if (!ap->mutex_fork)
		return (1);
	if (pthread_mutex_init(&ap->death, NULL) != 0)
		return (1);
	i = -1;
	while (++i < ap->nbr)
	{
		if (pthread_mutex_init(&ap->mutex_fork[i], NULL) != 0)
			break ;
	}
	if (i != ap->nbr)
	{
		while (--i >= 0)
		{
			if (pthread_mutex_destroy(&ap->mutex_fork[i]) != 0)
				return (1);
		}
	}
	return (0);
}	

int	fill_param(int argc, t_param *ap, char **argv)
{
	ap->nbr = ft_atoi(argv[1]);
	ap->die = ft_atoi(argv[2]);
	ap->eat = ft_atoi(argv[3]);
	ap->sleep = ft_atoi(argv[4]);
	if (argc == 6)
		ap->infinite = ft_atoi(argv[5]);
	if (ap->nbr <= 0 || ap->die <= 0 || ap->eat < 0
		|| ap->sleep < 0
		|| (argc == 6 && ap->infinite <= 0))
		return (1);
	ap->stop = 1;
	if (ap->nbr % 2)
		ap->many = 1;
	if (ap->eat > ap->sleep)
		ap->think = (ap->eat - ap->sleep) + (ap->eat * ap->many);
	memset(ap->fork, true, sizeof(bool) * ap->nbr);
	return (0);
}

int	init_ap(t_param *ap, int argc, char **argv)
{
	ap->th = malloc(sizeof(struct thread_args *) * ft_atoi(argv[1]));
	ap->fork = malloc(sizeof(bool) * ft_atoi(argv[1]));
	if (!ap->th || !ap->fork)
		return (1);
	if (fill_param(argc, ap, argv))
		return (1);
	if (init_mutex(ap) != 0)
		return (1);
	return (0);
}

int	init_to_null(t_param **ap)
{
	*ap = malloc(sizeof(t_param));
	if (!(*ap))
		return (1);
	memset((*ap), 0, sizeof(t_param));
	(*ap)->mutex_fork = NULL;
	(*ap)->th = NULL;
	return (0);
}

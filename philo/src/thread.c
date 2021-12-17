/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 20:34:01 by zcanales          #+#    #+#             */
/*   Updated: 2021/12/17 16:10:32 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <stdlib.h>
#include <sys/time.h>

void	*routine(void *arg)
{
	t_philo	philo;

	philo = *(t_philo *)arg;
	while (!(philo.ap->timestamp.tv_sec + philo.ap->timestamp.tv_usec))
		usleep(10);
	gettimeofday(&philo.start_eat, NULL);
	even_synchronization(&philo);
	pthread_mutex_lock(&philo.ap->death);
	while (philo.ap->stop)
	{
		pthread_mutex_unlock(&philo.ap->death);
		if (check_any_death(&philo))
			break ;
		ft_eat(&philo);
		if (check_any_death(&philo))
			break ;
		ft_sleep(&philo);
		if (check_any_death(&philo))
			break ;
		ft_think(&philo);
		pthread_mutex_lock(&philo.ap->death);
	}
	pthread_mutex_unlock(&philo.ap->death);
	free(arg);
	return (NULL);
}

int	join_thread(t_param *ap)
{
	int	i;

	i = -1;
	while (++i < ap->nbr)
	{
		if (pthread_join(ap->th[i], NULL) != 0)
			return (1);
	}
	i = -1;
	while (++i < ap->nbr)
	{
		if (pthread_mutex_destroy(&ap->mutex_fork[i]))
			return (1);
	}
	if (pthread_mutex_destroy(&ap->death))
		return (1);
	return (0);
}

int	create_thread(t_param *ap)
{
	int		i;
	t_philo	*philo;

	i = -1;
	ap->timestamp.tv_sec = 0;
	ap->timestamp.tv_usec = 0;
	while (++i < ap->nbr)
	{
		philo = malloc(sizeof (t_philo));
		if (!philo)
			return (1);
		init_philo(philo, i, ap);
		if (pthread_create(&ap->th[i], NULL, &routine, philo) != 0)
			return (1);
	}
	gettimeofday(&ap->timestamp, NULL);
	return (0);
}

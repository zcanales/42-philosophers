/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 14:09:57 by zcanales          #+#    #+#             */
/*   Updated: 2021/12/17 16:10:08 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <sys/time.h>
#include <stdio.h>

long int	get_time(t_philo *philo)
{
	long int		during;

	gettimeofday(&philo->start_action, NULL);
	during = (philo->start_action.tv_sec * 1000
			+ philo->start_action.tv_usec / 1000)
		- (philo->ap->timestamp.tv_sec * 1000
			+ philo->ap->timestamp.tv_usec / 1000);
	return (during);
}

int	check_any_death(t_philo *philo)
{
	int	during;

	pthread_mutex_lock(&philo->ap->death);
	if (!philo->ap->stop)
	{
		pthread_mutex_unlock(&philo->ap->death);
		return (1);
	}
	gettimeofday(&philo->check_die, NULL);
	during = (philo->check_die.tv_sec * 1000 + philo->check_die.tv_usec / 1000)
		- (philo->start_eat.tv_sec * 1000 + philo->start_eat.tv_usec / 1000);
	if (during < philo->ap->die)
	{
		pthread_mutex_unlock(&philo->ap->death);
		return (0);
	}
	philo->ap->stop = 0;
	printf("%ld %d died\n", get_time(philo), philo->index + 1);
	pthread_mutex_unlock(&philo->ap->death);
	return (1);
}

void	even_synchronization(t_philo *philo)
{
	if (!(philo->index % 2))
	{
			ft_usleep(philo->ap->eat * 1000 / 2, philo);
		if (philo->index == (philo->ap->nbr - 1))
		{
			ft_usleep(philo->ap->eat * 1000 / 2 + 1000, philo);
			philo->ap->many = 1;
		}
	}
}

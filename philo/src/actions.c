/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 11:08:23 by zcanales          #+#    #+#             */
/*   Updated: 2021/12/17 16:16:22 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <sys/time.h>
#include <stdio.h>

static void	ft_eat_start(t_philo *philo)
{
	if (philo->ap->eat == 0)
		return ;
	gettimeofday(&philo->start_eat, NULL);
	printf("%ld %d is eating\n",
		get_time(philo), philo->index + 1);
	ft_usleep(philo->ap->eat * 1000, philo);
	philo->time++;
	if (philo->time == philo->ap->infinite && philo->ap->infinite)
	{
		pthread_mutex_lock(&philo->ap->death);
		philo->ap->time++;
		if (philo->ap->time == philo->ap->nbr)
		{
			philo->ap->stop = 0;
			pthread_mutex_unlock(&philo->ap->death);
		}
		else
			pthread_mutex_unlock(&philo->ap->death);
	}
}

static int	take_two_forks(t_philo *philo, int first, int second)
{
	if (ft_mutex_trylock(philo, first))
		return (1);
	else
		printf("%ld %d has taken a fork\n", get_time(philo),
			philo->index + 1);
	if (ft_mutex_trylock(philo, second))
		return (1);
	else
		printf("%ld %d has taken a fork\n", get_time(philo),
			philo->index + 1);
	if (check_any_death(philo))
		return (1);
	return (0);
}

int	ft_eat(t_philo *philo)
{
	if (take_two_forks(philo, philo->index, philo->next))
		return (1);
	ft_eat_start(philo);
	pthread_mutex_lock(&philo->ap->mutex_fork[philo->index]);
	philo->ap->fork[philo->index] = true;
	pthread_mutex_unlock(&philo->ap->mutex_fork[philo->index]);
	pthread_mutex_lock(&philo->ap->mutex_fork[philo->next]);
	philo->ap->fork[philo->next] = true;
	pthread_mutex_unlock(&philo->ap->mutex_fork[philo->next]);
	return (0);
}

void	ft_sleep(t_philo *philo)
{
	printf("%ld %d is sleeping\n", get_time(philo),
		philo->index + 1);
	ft_usleep(philo->ap->sleep * 1000, philo);
}

void	ft_think(t_philo *philo)
{
	gettimeofday(&philo->start_action, NULL);
	printf("%ld %d is thinking\n", get_time(philo),
		philo->index + 1);
	ft_usleep(philo->ap->think * 1000, philo);
}

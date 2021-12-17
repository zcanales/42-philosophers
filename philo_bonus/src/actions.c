/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 11:08:23 by zcanales          #+#    #+#             */
/*   Updated: 2021/12/15 19:05:55 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"
#include <sys/time.h>
#include <stdio.h>

void	speak(t_philo *philo, char *str)
{
	int	during;

	sem_wait(philo->ap->sem_print);
	gettimeofday(&philo->start_action, NULL);
	during = get_time_2(philo->start_action, philo->ap->timestamp);
	printf("%d %d %s", during, philo->index + 1, str);
	sem_post(philo->ap->sem_print);
}

static void	ft_eat_start(t_philo *philo)
{
	if (philo->ap->eat == 0)
		return ;
	gettimeofday(&philo->ap->start_eat, NULL);
	speak(philo, "is eating\n");
	ft_usleep(philo->ap->eat * 1000, philo);
}

void	ft_eat(t_philo *philo)
{	
	sem_wait(philo->ap->sem_fork);
	speak(philo, "has taken a fork\n");
	sem_wait(philo->ap->sem_fork);
	speak(philo, "has taken a fork\n");
	ft_eat_start(philo);
	sem_post(philo->ap->sem_fork);
	sem_post(philo->ap->sem_fork);
	sem_wait(philo->ap->sem_death);
	philo->ap->time++;
	if (philo->ap->infinite && philo->ap->time == philo->ap->infinite)
	{
		sem_post(philo->ap->sem_death);
		usleep(10000);
	}
	sem_post(philo->ap->sem_death);
}

void	ft_sleep(t_philo *philo)
{
	speak(philo, "is sleeping\n");
	ft_usleep(philo->ap->sleep * 1000, philo);
}

void	ft_think(t_philo *philo)
{
	speak(philo, "is thinking\n");
	if (philo->ap->nbr % 2)
		ft_usleep(philo->ap->think * 1000, philo);
}

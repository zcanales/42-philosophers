/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 20:34:01 by zcanales          #+#    #+#             */
/*   Updated: 2021/12/17 16:11:20 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"
#include <signal.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

void	*routine(void *arg)
{
	t_philo	*philo;
	int		during;

	philo = (t_philo *)arg;
	while (1)
	{
		sem_wait(philo->ap->sem_death);
		gettimeofday(&philo->check_die, NULL);
		during = get_time_2(philo->check_die, philo->ap->start_eat);
		if (during > philo->ap->die)
		{
			speak(philo, "died\n");
			sem_wait(philo->ap->sem_print);
			sem_post(philo->ap->sem_death);
			exit (1);
		}
		if (philo->ap->infinite && philo->ap->time == philo->ap->infinite)
		{
			sem_post(philo->ap->sem_death);
			exit (0);
		}
		sem_post(philo->ap->sem_death);
		usleep(900);
	}
	return (NULL);
}

void	child_process(t_philo *philo)
{
	gettimeofday(&philo->ap->start_eat, NULL);
	if (pthread_create(&philo->ap->th, NULL, &routine, philo) != 0)
		return ;
	even_synchronization(philo);
	while (1)
	{
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
	if (pthread_join(philo->ap->th, NULL) != 0)
		return ;
}

int	create_process(t_param *ap)
{
	int		i;
	t_philo	*philo;

	i = -1;
	philo = malloc(sizeof (t_philo));
	if (!philo)
		return (1);
	init_philo(philo, ap);
	while (++i < ap->nbr)
	{
		philo->index = i;
		philo->ap->pid[i] = fork();
		if (philo->ap->pid[i] == -1)
			return (1);
		if (philo->ap->pid[i] == 0)
			break ;
	}
	if (philo->ap->pid[philo->index] != 0)
		mother_process(philo);
	else
	{
		free(philo->ap->pid);
		child_process(philo);
	}
	return (0);
}

void	mother_process(t_philo *philo)
{
	int	i;
	int	status;

	i = -1;
	while (++i < philo->ap->nbr)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
		{
			i = -1;
			while (++i < philo->ap->nbr)
				kill(philo->ap->pid[i], SIGKILL);
			break ;
		}
	}
	sem_close(philo->ap->sem_death);
	sem_close(philo->ap->sem_fork);
	sem_close(philo->ap->sem_death);
	sem_unlink("/sem_death");
	sem_unlink("/sem_fork");
	sem_unlink("/sem_print");
	free(philo);
}

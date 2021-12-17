/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 13:55:44 by zcanales          #+#    #+#             */
/*   Updated: 2021/12/17 16:11:46 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"
#include <string.h>
#include <fcntl.h>          /* O_CREAT, O_EXEC          */
#include <sys/types.h>
#include <sys/time.h>
#include <stdlib.h>

void	init_philo(t_philo *philo, t_param *ap)
{
	memset(philo, 0, sizeof(t_philo));
	philo->ap = ap;
	gettimeofday(&philo->ap->timestamp, NULL);
}

int	create_semaphore(t_param *ap)
{
	sem_unlink("/sem_death");
	sem_unlink("/sem_fork");
	sem_unlink("/sem_print");
	ap->sem_death = sem_open("/sem_death", O_CREAT | O_EXCL, 0644, 1);
	ap->sem_print = sem_open("/sem_print", O_CREAT | O_EXCL, 0644, 1);
	ap->sem_fork = sem_open("/sem_fork", O_CREAT | O_EXCL, 0644, ap->nbr);
	if (ap->sem_death == SEM_FAILED
		|| ap->sem_fork == SEM_FAILED
		|| ap->sem_print == SEM_FAILED)
		return (1);
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
	if (ap->nbr <= 0 || ap->die <= 0
		|| ap->eat < 0 || ap->sleep < 0
		|| (ap->infinite <= 0 && argc == 6))
		return (1);
	ap->stop = 1;
	if (ap->nbr % 2)
		ap->many = 1;
	ap->think = (ap->eat - ap->sleep) + (ap->eat * ap->many);
	return (0);
}

int	init_ap(t_param *ap, int argc, char **argv)
{
	ap->pid = malloc(sizeof(pid_t) * ft_atoi(argv[1]));
	if (!ap->pid)
		return (1);
	if (fill_param(argc, ap, argv))
		return (1);
	if (create_semaphore(ap))
		return (1);
	return (0);
}

int	init_to_null(t_param **ap)
{
	*ap = malloc(sizeof(t_param));
	if (!(*ap))
		return (1);
	memset((*ap), 0, sizeof(t_param));
	return (0);
}

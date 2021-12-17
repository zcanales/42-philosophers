/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 14:50:07 by zcanales          #+#    #+#             */
/*   Updated: 2021/12/15 19:11:51 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <sys/time.h>

int	ft_atoi(const char *str)
{
	int				i;
	unsigned int	sum;

	sum = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+')
		i++;
	while (str[i] <= '9' && str[i] >= '0')
	{
		sum = (sum * 10) + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0')
		return (-1);
	if (sum > 2147483647)
		return (-1);
	return (sum);
}

int	ft_usleep(int action_lenght, t_philo *philo)
{
	struct timeval	start;
	struct timeval	end;
	int				during;
	int				i;

	i = 0;
	during = 0;
	gettimeofday(&start, NULL);
	while (during < action_lenght)
	{
		gettimeofday(&end, NULL);
		during = ((end.tv_sec * 1000000 + end.tv_usec)
				- (start.tv_sec * 1000000 + start.tv_usec));
		usleep(1 * philo->ap->nbr);
		if (during - i > 10000)
		{
			i += 10000;
			if (check_any_death(philo))
				return (1);
		}
	}
	if (!check_any_death(philo))
		return (0);
	return (1);
}

int	ft_mutex_trylock(t_philo *philo, int i)
{
	pthread_mutex_lock(&philo->ap->mutex_fork[i]);
	while (philo->ap->fork[i] == false)
	{
		pthread_mutex_unlock(&philo->ap->mutex_fork[i]);
		if (ft_usleep(1 * philo->ap->nbr, philo))
			return (1);
		pthread_mutex_lock(&philo->ap->mutex_fork[i]);
	}
	philo->ap->fork[i] = false;
	pthread_mutex_unlock(&philo->ap->mutex_fork[i]);
	return (0);
}

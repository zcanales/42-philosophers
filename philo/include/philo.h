/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 10:53:07 by zcanales          #+#    #+#             */
/*   Updated: 2021/12/15 19:11:47 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <pthread.h>
# include <stdbool.h>

typedef struct s_param
{
	int				infinite;
	int				many;
	int				nbr;
	int				die;
	int				eat;
	int				sleep;
	int				think;
	int				stop;
	int				time;
	struct timeval	timestamp;
	bool			*fork;
	pthread_mutex_t	*mutex_fork;
	pthread_mutex_t	death;
	pthread_t		*th;
}t_param;

typedef struct s_philo
{
	int				index;
	int				next;
	int				time;
	struct timeval	start_eat;
	struct timeval	check_die;
	struct timeval	start_action;
	t_param			*ap;
}t_philo;

/*	INIT	*/
int			init_to_null(t_param **ap);
int			init_ap(t_param *ap, int argc, char **argv);
int			fill_param(int argc, t_param *ap, char **argv);
int			init_mutex(t_param *ap);
int			init_philo(t_philo *philo, int i, t_param *ap);

/*	THREAD	*/
int			create_thread(t_param *ap);
void		*routine(void *arg);
int			join_thread(t_param *ap);

/*	MAIN	*/
int			msg_error(t_param *ap, char *str, int err);

/*	GET TIME	*/
long int	get_time(t_philo *philo);
int			check_any_death(t_philo *philo);
void		even_synchronization(t_philo *philo);

/*	ACTIONS	*/
void		ft_think(t_philo *table);
void		ft_sleep(t_philo *table);
int			ft_eat(t_philo *table);

/*	UTILS */
int			ft_atoi(const char *str);
int			ft_usleep(int action_lenght, t_philo *pthilo);
int			ft_mutex_trylock(t_philo *philo, int i);
#endif

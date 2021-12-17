/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 10:53:07 by zcanales          #+#    #+#             */
/*   Updated: 2021/12/15 19:05:53 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <unistd.h>
# include <semaphore.h>

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
	struct timeval	start_eat;
	pid_t			*pid;
	sem_t			*sem_death;
	sem_t			*sem_fork;
	sem_t			*sem_print;
	pthread_t		th;
}t_param;

typedef struct s_philo
{
	int				index;
	int				next;
	int				time;
	struct timeval	check_die;
	struct timeval	start_action;
	t_param			*ap;
}t_philo;

/*	INIT	*/
int			init_to_null(t_param **ap);
int			init_ap(t_param *ap, int argc, char **argv);
int			fill_param(int argc, t_param *ap, char **argv);
int			init_mutex(t_param *ap);
void		init_philo(t_philo *philo, t_param *ap);

/*	THREAD	*/
int			create_process(t_param *ap);
void		mother_process(t_philo *philo);

/*	MAIN	*/
int			msg_error(t_param *ap, char *str, int err);

/*	GET TIME	*/
long int	get_time_2(struct timeval time, struct timeval start);
int			ft_usleep(int action_lenght, t_philo *pthilo);

/*	ACTIONS	*/
void		ft_think(t_philo *table);
void		ft_sleep(t_philo *table);
void		ft_eat(t_philo *table);
void		speak(t_philo *philo, char *str);

/*	UTILS */
int			ft_atoi(const char *str);
void		even_synchronization(t_philo *philo);
#endif

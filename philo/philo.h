/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhourba <ykhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 13:14:21 by ykhourba          #+#    #+#             */
/*   Updated: 2023/04/06 17:29:41 by ykhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include<stdio.h>
# include<unistd.h>
# include<pthread.h>
# include<stdlib.h> 
# include<sys/time.h>

typedef struct s_info
{
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				m_meals;
	int				check_death;
	int				nbr_of_philo;
	unsigned long	start_time;
	pthread_mutex_t	print;
	pthread_mutex_t	meal;
	pthread_mutex_t	deid;
}	t_info;

typedef struct s_philo
{
	pthread_t		th;
	pthread_mutex_t	*fork;
	int				pos;
	unsigned long	lst_eat;
	int				nbr_meal;
	pthread_mutex_t	*next_fork;
	t_info			*info;
}	t_philo;

int				ft_atoi(const char *str);
int				not_nbr(char *str);
int				valid_args(int argc, char **argv);
void			ft_print_errors(void);
unsigned long	current_time(void);
t_info			*data_init(int argc, char **argv);
t_philo			**init_philos(t_info *data, pthread_mutex_t **forks);
void			mutexes_init(pthread_mutex_t *forks, int mutex_nums);
void			check_death(t_philo **ph);
void			*lifecycle(void *ph);
void			ft_sleep(t_philo *ph);
void			eat(t_philo *ph);
void			ft_print(t_philo *ph, char *str);
void			manage_threads(t_philo **philo);
void			ft_sleep_time(int time);
void			one_philo(t_philo *ph, t_info *data);
#endif
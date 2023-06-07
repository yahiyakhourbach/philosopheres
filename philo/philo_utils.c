/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhourba <ykhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 15:48:33 by ykhourba          #+#    #+#             */
/*   Updated: 2023/04/06 17:28:33 by ykhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print(t_philo *ph, char *str)
{
	t_info	*data;

	data = ph->info;
	pthread_mutex_lock(&data->print);
	printf("%lu %d %s", (current_time() - data->start_time), ph->pos, str);
	pthread_mutex_unlock(&data->print);
}

void	eat(t_philo *ph)
{
	t_info	*data;

	data = ph->info;
	pthread_mutex_lock(ph->fork);
	ft_print(ph, "has taken a fork\n");
	pthread_mutex_lock(ph->next_fork);
	ft_print(ph, "has taken a fork\n");
	ft_print(ph, "is eating\n");
	ft_sleep_time(data->t_eat);
	pthread_mutex_lock(&data->meal);
	ph->lst_eat = current_time();
	ph->nbr_meal++;
	pthread_mutex_unlock(&data->meal);
	pthread_mutex_unlock(ph->fork);
	pthread_mutex_unlock(ph->next_fork);
}

void	ft_sleep(t_philo *ph)
{
	t_info	*data;

	data = ph->info;
	ft_print(ph, "is sleeping\n");
	ft_sleep_time(data->t_sleep);
}

void	ft_sleep_time(int time)
{
	unsigned long	ms_start;

	ms_start = current_time();
	while (current_time() - ms_start < (unsigned long)time)
		usleep(200);
}

void	one_philo(t_philo *ph, t_info *data)
{
	if (data->nbr_of_philo == 1)
	{
		ft_print(ph, "has taken a fork\n");
		usleep(data->t_die * 1000);
		return ;
	}
}

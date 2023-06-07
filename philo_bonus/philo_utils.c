/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhourba <ykhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 17:13:01 by ykhourba          #+#    #+#             */
/*   Updated: 2023/04/06 18:28:20 by ykhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print(t_philo *ph, char *str)
{
	t_info	*data;

	data = ph->info;
	sem_wait(data->print);
	printf("%lu %d %s", (current_time() - data->start_time), ph->pos, str);
	sem_post(data->print);
}

void	eat(t_philo *ph)
{
	t_info	*data;

	data = ph->info;
	sem_wait(data->forks);
	ft_print(ph, "has taken a fork\n");
	sem_wait(data->forks);
	ft_print(ph, "has taken a fork\n");
	ft_print(ph, "is eating\n");
	ft_sleep_time(data->t_eat);
	sem_wait(ph->meal);
	ph->lst_eat = current_time();
	ph->nbr_meal++;
	sem_post(ph->meal);
	sem_post(data->forks);
	sem_post(data->forks);
}

void	ft_sleep(t_philo *ph)
{
	t_info	*data;

	data = ph->info;
	ft_print(ph, "is sleeping\n");
	ft_sleep_time(data->t_sleep);
}

unsigned long	current_time(void)
{
	struct timeval	time;
	unsigned long	c_time;

	gettimeofday(&time, NULL);
	c_time = (time.tv_usec / 1000) + (time.tv_sec * 1000);
	return (c_time);
}

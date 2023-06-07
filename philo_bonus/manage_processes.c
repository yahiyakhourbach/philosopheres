/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_processes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhourba <ykhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:41:40 by ykhourba          #+#    #+#             */
/*   Updated: 2023/04/06 17:40:50 by ykhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*lifecycle(void *ph)
{
	t_philo	*philo;
	t_info	*data;
	int		i;

	i = -1;
	philo = (t_philo *)ph;
	data = philo->info;
	if (philo->pos % 2)
	{
		while (++i < 200)
			usleep(1);
	}
	if (data->nbr_of_philo == 1)
	{
		ft_print(ph, "has taken a fork\n");
		usleep(data->t_die * 1000);
		return (NULL);
	}
	while (1)
	{
		eat(philo);
		ft_sleep(philo);
		ft_print(philo, "is thinking\n");
	}
	return (NULL);
}

void	check_death(t_philo *ph)
{
	t_info	*data;

	data = ph->info;
	while (1)
	{
		usleep(100);
		sem_wait(ph->meal);
		if (current_time() - ph->lst_eat > (unsigned long)data->t_die)
		{
			sem_wait(data->print);
			printf("%lu %d %s",
				(current_time() - data->start_time), ph->pos, "died");
			return ;
		}
		if (data->m_meals != -1 && ph->nbr_meal >= data->m_meals)
			return ;
		sem_post(ph->meal);
	}
}

static void	manage_philo(t_philo *ph)
{
	pthread_t	th;

	ph->lst_eat = current_time();
	pthread_create(&th, NULL, lifecycle, (void *)ph);
	pthread_detach(th);
	check_death(ph);
}

void	manage_processes(t_philo **philo)
{
	int		i;
	t_info	*data;
	int		pid;

	data = philo[0]->info;
	i = 0;
	while (i < data->nbr_of_philo)
	{
		pid = fork();
		if (pid == 0)
		{
			manage_philo(philo[i]);
			exit(0);
		}
		i++;
	}
}

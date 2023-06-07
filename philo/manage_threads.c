/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhourba <ykhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:41:40 by ykhourba          #+#    #+#             */
/*   Updated: 2023/04/06 17:28:09 by ykhourba         ###   ########.fr       */
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
		while (++i < 500)
			usleep(1);
	}
	one_philo(philo, data);
	while (1)
	{
		eat(ph);
		pthread_mutex_lock(&data->deid);
		if (!data->check_death)
			return (NULL);
		pthread_mutex_unlock(&data->deid);
		ft_sleep(ph);
		ft_print(ph, "is thinking\n");
	}
	return (NULL);
}

int	check_meals(t_philo **ph)
{
	t_info	*data;
	int		i;
	int		_bool;

	i = 0;
	_bool = 1;
	data = ph[0]->info;
	if (data->m_meals == -1)
		return (0);
	while (i < data->nbr_of_philo)
	{
		if (data->m_meals != -1 && ph[i]->nbr_meal < data->m_meals)
			_bool = 0;
		i++;
	}
	if (_bool)
		return (1);
	return (0);
}

static void	ft_check_lock(t_info *data)
{
	pthread_mutex_lock(&data->deid);
	data->check_death = 0;
	pthread_mutex_unlock(&data->deid);
}

void	check_death(t_philo **ph)
{
	t_info	*data;
	int		i;

	data = ph[0]->info;
	i = 0;
	while (1)
	{
		pthread_mutex_lock(&data->meal);
		if (i == data->nbr_of_philo)
			i = 0;
		if (current_time() - ph[i]->lst_eat > (unsigned long)data->t_die
			|| check_meals(ph))
		{
			ft_check_lock(data);
			pthread_mutex_lock(&data->print);
			if (data->m_meals == -1)
				printf("%lu %d %s",
					(current_time() - data->start_time), ph[i]->pos, "died");
			break ;
		}
		pthread_mutex_unlock(&data->meal);
		i++;
	}
}

void	manage_threads(t_philo **philo)
{
	int		i;
	t_info	*data;

	data = philo[0]->info;
	i = -1;
	while (++i < data->nbr_of_philo)
		philo[i]->lst_eat = current_time();
	i = 0;
	while (i < data->nbr_of_philo)
	{
		pthread_create(&philo[i]->th, NULL, lifecycle, (void *)philo[i]);
		i++;
	}
	i = 0;
	while (i < data->nbr_of_philo)
		pthread_detach(philo[i++]->th);
	check_death(philo);
}

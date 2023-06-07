/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhourba <ykhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 17:38:29 by ykhourba          #+#    #+#             */
/*   Updated: 2023/03/30 14:57:53 by ykhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_info(t_info *data)
{
	if (data->nbr_of_philo < 1 || data->t_die == 0
		|| data->t_eat == 0 || data->t_sleep == 0
		|| data->m_meals == 0)
		return (0);
	return (1);
}

t_info	*data_init(int argc, char **argv)
{
	t_info	*data;

	data = malloc(sizeof(t_info));
	if (!data)
		return (NULL);
	data->nbr_of_philo = ft_atoi(argv[1]);
	data->t_die = ft_atoi(argv[2]);
	data->t_eat = ft_atoi(argv[3]);
	data->t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->m_meals = ft_atoi(argv[5]);
	else
		data->m_meals = -1;
	data->start_time = current_time();
	data->check_death = 1;
	if (!check_info(data))
		return (free(data), NULL);
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->meal, NULL);
	pthread_mutex_init(&data->deid, NULL);
	return (data);
}

static void	ft_free(t_philo **ph, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		free(ph[i]);
		i++;
	}
	free(ph);
}

t_philo	**init_philos(t_info *data, pthread_mutex_t **forks)
{
	int				i;
	t_philo			**ph;
	pthread_mutex_t	*fork;

	i = 0;
	fork = *forks;
	ph = (t_philo **)malloc(sizeof(t_philo *) * data->nbr_of_philo);
	if (!ph)
		return (NULL);
	while (i < data->nbr_of_philo)
	{
		ph[i] = malloc(sizeof(t_philo));
		if (!ph[i])
			return (ft_free(ph, i), NULL);
		ph[i]->pos = i + 1;
		ph[i]->info = data;
		ph[i]->fork = &fork[i];
		ph[i]->next_fork = &(fork[(i + 1) % data->nbr_of_philo]);
		i++;
	}
	return (ph);
}

void	mutexes_init(pthread_mutex_t *forks, int mutex_nums)
{
	int	i;

	i = 0;
	while (i < mutex_nums)
		pthread_mutex_init(&forks[i++], NULL);
}

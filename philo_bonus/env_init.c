/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhourba <ykhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 17:38:29 by ykhourba          #+#    #+#             */
/*   Updated: 2023/03/31 15:09:25 by ykhourba         ###   ########.fr       */
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

static void	ft_sem_init(t_info **data)
{
	t_info	*info;

	info = *data;
	sem_unlink("forks");
	sem_unlink("print");
	info->forks = sem_open("forks", O_CREAT, 0644, info->nbr_of_philo);
	info->print = sem_open("print", O_CREAT, 0644, 1);
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
	ft_sem_init(&data);
	return (data);
}

t_philo	**init_philos(t_info *data)
{
	int		i;
	t_philo	**ph;
	char	*sem_name;

	i = 0;
	ph = (t_philo **)malloc(sizeof(t_philo *) * data->nbr_of_philo);
	while (i < data->nbr_of_philo)
	{
		sem_name = ft_itoa(i);
		ph[i] = malloc(sizeof(t_philo));
		ph[i]->pos = i + 1;
		ph[i]->info = data;
		ph[i]->nbr_meal = 0;
		sem_unlink(sem_name);
		ph[i]->meal = sem_open(sem_name, O_CREAT | O_EXCL, 0644, 1);
		free(sem_name);
		i++;
	}
	return (ph);
}

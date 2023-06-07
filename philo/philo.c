/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhourba <ykhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 14:31:42 by ykhourba          #+#    #+#             */
/*   Updated: 2023/04/06 17:45:45 by ykhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_free(t_philo **ph)
{
	int		i;
	t_info	*data;
	int		nbr;

	i = 0;
	data = ph[0]->info;
	nbr = data->nbr_of_philo;
	free(data);
	while (i < nbr)
	{
		free(ph[i]);
		i++;
	}
	free(ph);
}

int	main(int argc, char **argv)
{
	t_info			*data;
	t_philo			**philo;
	pthread_mutex_t	*forks;

	if (!valid_args(argc, argv))
		return (ft_print_errors(), 1);
	else
	{
		data = data_init(argc, argv);
		if (!data)
			return (ft_print_errors(), 3);
		forks = malloc(sizeof(pthread_mutex_t) * data->nbr_of_philo);
		if (!forks)
			return (free(data), 3);
		philo = init_philos(data, &forks);
		if (!philo)
			return (free(data), free(forks), 4);
		mutexes_init(forks, data->nbr_of_philo);
		manage_threads(philo);
		free(forks);
		ft_free(philo);
	}
}

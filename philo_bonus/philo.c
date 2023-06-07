/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhourba <ykhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 14:31:42 by ykhourba          #+#    #+#             */
/*   Updated: 2023/04/06 17:36:32 by ykhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_kill_processes(t_philo **philo, int nbr)
{
	int		i;
	t_info	*data;

	data = philo[0]->info;
	sem_close(data->forks);
	sem_close(data->print);
	i = 0;
	while (i < nbr)
	{
		sem_close(philo[i]->meal);
		i++;
	}
}

static void	ft_free(t_philo **ph, int nbr)
{
	int	i;

	i = 0;
	while (i < nbr)
	{
		free(ph[i]);
		i++;
	}
	free(ph);
}

static void	waiting_childs(t_philo **ph, t_info *data)
{
	if (data->m_meals == -1)
	{
		waitpid(-1, NULL, 0);
		kill(0, SIGINT);
	}
	else
		while (waitpid(0, NULL, 0) != -1)
			;
	ft_kill_processes(ph, data->nbr_of_philo);
	ft_free(ph, data->nbr_of_philo);
	free(data);
}

int	main(int argc, char **argv)
{
	t_info		*data;
	t_philo		**philo;

	if (!valid_args(argc, argv))
		return (ft_print_errors(), 1);
	else
	{
		data = data_init(argc, argv);
		if (!data)
			return (ft_print_errors(), 2);
		philo = init_philos(data);
		if (!philo)
			return (free(data), 3);
		manage_processes(philo);
		waiting_childs(philo, data);
	}
}

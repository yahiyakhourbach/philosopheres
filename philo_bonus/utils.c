/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhourba <ykhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 12:57:42 by ykhourba          #+#    #+#             */
/*   Updated: 2023/04/06 17:26:46 by ykhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	signe;
	int	res;

	if (!str)
		return (0);
	signe = 1;
	res = 0;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
	signe *= -1;
	if (*str == '-' || *str == '+')
	str++;
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	return (res * signe);
}

int	not_nbr(char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (1);
		str++;
	}
	return (0);
}

int	valid_args(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc != 5 && argc != 6)
		return (0);
	while (i < argc)
	{
		if (not_nbr(argv[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_print_errors(void)
{
	printf("please insert 4 or 5  valid args\n");
	printf("number of philos:\n");
	printf("time to die:\n");
	printf("time to east:\n");
	printf("time to sleep:\n");
	printf("number of times each philo need to eat(optional):\n");
}

void	ft_sleep_time(int time)
{
	unsigned long	ms_start;

	ms_start = current_time();
	while (current_time() - ms_start < (unsigned long)time)
		usleep(200);
}

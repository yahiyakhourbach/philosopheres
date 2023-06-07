/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhourba <ykhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:53:31 by ykhourba          #+#    #+#             */
/*   Updated: 2023/03/30 23:51:36 by ykhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long	trns_num(int nbr)
{
	long	num;

	if (nbr < 0)
		num = (long)nbr * -1;
	else
		num = (long)nbr;
	return (num);
}

static int	num_len(int num)
{
	int		len;
	long	nbr;

	if (num == 0)
		return (1);
	len = 0;
	nbr = trns_num(num);
	if (num < 0)
		len++;
	while (nbr > 0)
	{
		nbr /= 10;
		len++;
	}
	return (len);
}

static int	power(int len)
{
	int	res;
	int	i;

	i = 0;
	res = 1;
	while (i < len - 1)
	{
		res *= 10;
		i++;
	}
	return (res);
}

static void	arr_fill(char *arr, int len, int size, int num)
{
	int		i;
	long	nbr;

	nbr = trns_num(num);
	arr[0] = '/';
	i = 1;
	if (num < 0)
	{
		arr[i] = '-';
		i++;
	}
	while (i < len + 1)
	{
		arr[i] = nbr / size + '0';
		nbr %= size;
		size /= 10;
		i++;
	}
	arr[i] = '\0';
}

char	*ft_itoa(int num)
{
	int		len;
	int		size;
	char	*arr;

	len = num_len(num);
	if (num > 0)
		size = power(len);
	else
		size = power(len - 1);
	arr = malloc(sizeof(char) * (len + 2));
	if (!arr)
		return (NULL);
	arr_fill(arr, len, size, num);
	return (arr);
}

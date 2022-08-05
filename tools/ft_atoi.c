/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoutaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 02:56:41 by kmoutaou          #+#    #+#             */
/*   Updated: 2022/06/20 02:58:44 by kmoutaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

static int	ft_convert(const char *str, int i, int result, int sign)
{
	while (ft_isdigit(str[i]))
	{
		if ((((unsigned long)result * 10) + (str[i] - '0'))
			> (unsigned long)9223372036854775807 && sign > 0)
			return (-1);
		if ((((unsigned long)result * 10) + (str[i] - '0'))
			> (unsigned long)9223372036854775807 + 1 && sign < 0)
			return (0);
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;
	int	i;
	int	repeat;

	repeat = 0;
	result = 0;
	sign = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	result = ft_convert(str, i, result, sign);
	return (result);
}

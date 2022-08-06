/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoutaou <kmoutaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 03:53:18 by kmoutaou          #+#    #+#             */
/*   Updated: 2022/08/06 04:56:52 by kmoutaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	p_usleep(int t)
{
	long long	tmp_t;

	tmp_t = get_time();
	usleep(t * 0.9);
	while (get_time() < tmp_t + t)
		usleep(100);
}

/*long long	transform_ms(struct timeval t)
{
	long long	tmp_t;

	tmp_t = (t.tv_sec * 1000 + t.tv_usec / 1000);
	return (tmp_t);
}*/

long long	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return(t.tv_sec * 1000 + t.tv_usec / 1000);
}

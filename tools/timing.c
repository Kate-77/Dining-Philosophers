/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoutaou <kmoutaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 03:53:18 by kmoutaou          #+#    #+#             */
/*   Updated: 2022/08/11 14:49:37 by kmoutaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	p_usleep(int t)
{
	long long	tmp_t;

	tmp_t = get_time();
	while (get_time() < tmp_t + t)
		usleep(300);
}

long long	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

void	display(t_thread *philo, char *str)
{
	long long		time;

	pthread_mutex_lock(&philo->philo_infos->display_protector);
	time = get_time() - philo->philo_infos->start;
	pthread_mutex_lock(&philo->philo_infos->death_protector);
	if (!philo->philo_infos->death)
	{
		pthread_mutex_unlock(&philo->philo_infos->death_protector);
		printf("%lld\t%d\t%s\n", time, philo->t_id + 1, str);
	}
	else
		pthread_mutex_unlock(&philo->philo_infos->death_protector);
	pthread_mutex_unlock(&philo->philo_infos->display_protector);
}

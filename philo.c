/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoutaou <kmoutaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 01:46:01 by kmoutaou          #+#    #+#             */
/*   Updated: 2022/08/05 04:45:15 by kmoutaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

void	display(th_data *philo, char *str)
{
	long long		time;

	pthread_mutex_lock(&philo->philo_infos->display_mutex);
	//gettimeofday(&now, NULL);
	//time = transform_ms(now) - transform_ms(philo->philo_infos->creation);
	//time = get_time() - philo->philo_infos->start;
	//time = transform_ms(philo->last_meal) - philo->philo_infos->start;
	time = get_time() - philo->philo_infos->start;;
	if (!philo->philo_infos->death)
		printf("%lld\t%d\t%s\n", time, philo->t_id + 1, str);
	pthread_mutex_unlock(&philo->philo_infos->display_mutex);
}

void	*t_handle(void *arg)
{
	th_data	*philosopher;

	philosopher = arg;

	if (philosopher->t_id % 2 == 0)
		p_usleep(philosopher->philo_infos->time_to_eat);
	while (!philosopher->philo_infos->death)
	{
		forks(philosopher);
		eating(philosopher);
		sleeping(philosopher);
		thinking(philosopher);
	}
	return (NULL);
}

void	check_args(int argc)
{
	if (argc != 5 && argc != 6)
	{	
		printf("Error\n");
		exit(0);
	}
	return ;
}

void	creation(data_thread *infos)
{
	int	i;

	i = 0;
	if (infos->philo->t_id % 2 == 0)
		p_usleep(infos->time_to_eat);
	while (i < infos->number_of_philosophers)
	{
		infos->philo[i].last_meal = infos->creation;
		pthread_create(infos->philo->threads, NULL, t_handle, &infos->philo[i]);
		i++;
	}
	return ;
}

int	main(int argc, char **argv)
{
	data_thread		*infos;
	//th_data			*philosopher;
	int				i;

	check_args(argc);
	infos = (data_thread *)malloc(sizeof(data_thread));
	initialize(infos, argc, argv);
	gettimeofday(&infos->creation, NULL);
	infos->start = get_time();
	creation(infos);
	if (monitoring(infos->philo) == 0)
		return (0);
	if (infos->number_of_eat != 0)
	{
		if (monitoring_times_eating(infos) == 0)
			return (0);
	}
	printf("dumb shit\n");
	i = 0;
	while (i < infos->number_of_philosophers)
	{
		pthread_join(infos->philo->threads[i], NULL);
		i++;
	}
	free(infos->philo);
	i = 0;
	while (i < infos->number_of_philosophers)
	{
		pthread_mutex_destroy(&infos->forks[i]);
		i++;
	}
	free(infos->forks);
	return (0);
}

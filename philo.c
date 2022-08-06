/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoutaou <kmoutaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 01:46:01 by kmoutaou          #+#    #+#             */
/*   Updated: 2022/08/06 05:23:32 by kmoutaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

void	display(th_data *philo, char *str)
{
	long long		time;

	pthread_mutex_lock(&philo->philo_infos->display_mutex);
	time = get_time() - philo->philo_infos->start;
	if (!philo->philo_infos->death)
		printf("%lld\t%d\t%s\n", time, philo->t_id + 1, str);
	pthread_mutex_unlock(&philo->philo_infos->display_mutex);
}

void	*t_handle(void *arg)
{
	th_data	*philosopher;

	philosopher = arg;
	if (philosopher->t_id % 2 != 0)
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

void	join_philo(data_thread *infos)
{
	int	i;

	i = 0;
	while (i < infos->number_of_philosophers)
	{
		pthread_join(infos->philo->threads[i], NULL);
		i++;
	}
	free(infos->philo);
	return ;
}

void	destroy_mutex(data_thread *infos)
{
	int	i;

	i = 0;
	while (i < infos->number_of_philosophers)
	{
		pthread_mutex_destroy(&infos->forks[i]);
		i++;
	}
	free(infos->forks);
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
		infos->philo[i].last_meal = infos->start;
		printf("lbedia last meal : %lld\n", infos->philo[i].last_meal - infos->start);
		pthread_create(infos->philo->threads, NULL, t_handle, &infos->philo[i]);
		i++;
	}
	return ;
}

int	main(int argc, char **argv)
{
	data_thread		*infos;

	check_args(argc);
	infos = (data_thread *)malloc(sizeof(data_thread));
	initialize(infos, argc, argv);
	infos->start = get_time();
	creation(infos);
	manage_monitoring(infos);
	join_philo(infos);
	destroy_mutex(infos);
	return (0);
}

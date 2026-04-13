/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenlee <jenlee@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 17:22:35 by jenlee            #+#    #+#             */
/*   Updated: 2025/12/16 17:22:35 by jenlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	abort_threads(t_rules *rules, int count)
{
	pthread_mutex_lock(&rules->end_mutex);
	rules->simulation_end = true;
	pthread_mutex_unlock(&rules->end_mutex);
	while (count > 0)
	{
		count--;
		pthread_join(rules->philo[count].thread, NULL);
	}
	return (0);
}

int	start_threads(t_rules *rules, pthread_t *monitor)
{
	int	i;

	i = 0;
	while (i < rules->nb_philo)
	{
		if (pthread_create(&rules->philo[i].thread, NULL,
				philo_routine, &rules->philo[i]) != 0)
			return (abort_threads(rules, i));
		i++;
	}
	if (pthread_create(monitor, NULL, monitor_routine, rules) != 0)
		return (abort_threads(rules, rules->nb_philo));
	pthread_mutex_lock(&rules->end_mutex);
	rules->start_time = get_time_ms();
	rules->threads_ready = true;
	pthread_mutex_unlock(&rules->end_mutex);
	return (1);
}

void	join_threads(t_rules *rules, pthread_t monitor)
{
	int	i;

	pthread_join(monitor, NULL);
	i = 0;
	while (i < rules->nb_philo)
	{
		pthread_join(rules->philo[i].thread, NULL);
		i++;
	}
}

void	wait_starting_gate(t_rules *rules)
{
	while (1)
	{
		pthread_mutex_lock(&rules->end_mutex);
		if (rules->threads_ready || rules->simulation_end)
		{
			pthread_mutex_unlock(&rules->end_mutex);
			break ;
		}
		pthread_mutex_unlock(&rules->end_mutex);
		usleep(100);
	}
}
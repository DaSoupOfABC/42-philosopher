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

int	start_threads(t_rules *rules, pthread_t *monitor)
{
	int	i;

	i = 0;
	while (i < rules->nb_philo)
	{
		if (pthread_create(&rules->philo[i].thread, NULL,
				philo_routine, &rules->philo[i]) != 0)
			return (0);
		i++;
	}
	if (pthread_create(monitor, NULL, monitor_routine, rules) != 0)
		return (0);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenlee <jenlee@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 19:05:07 by jenlee            #+#    #+#             */
/*   Updated: 2025/12/15 19:05:07 by jenlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	init_philos(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->nb_philo)
	{
		rules->philo[i].id = i + 1;
		rules->philo[i].left_fork = &rules->fork[i];
		rules->philo[i].right_fork = &rules->fork[(i + 1) % rules->nb_philo];
		rules->philo[i].meals_eaten = 0;
		rules->philo[i].last_meal_time = rules->start_time;
		rules->philo[i].rules = rules;
		if (pthread_mutex_init(&rules->philo[i].meal_mutex, NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

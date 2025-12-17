/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenlee <jenlee@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 19:46:03 by jenlee            #+#    #+#             */
/*   Updated: 2025/12/15 19:46:03 by jenlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	print_state(t_philo *philo, char *msg, bool is_death)
{
	long	timestamp;

	pthread_mutex_lock(&philo->rules->print_mutex);
	timestamp = get_time_ms() - philo->rules->start_time;
	if (is_death)
	{
		printf("%ld %d %s\n", timestamp, philo->id, msg);
		pthread_mutex_lock(&philo->rules->end_mutex);
		philo->rules->simulation_end = true;
		pthread_mutex_unlock(&philo->rules->end_mutex);
		pthread_mutex_unlock(&philo->rules->print_mutex);
		return ;
	}
	pthread_mutex_lock(&philo->rules->end_mutex);
	if (!philo->rules->simulation_end)
		printf("%ld %d %s\n", timestamp, philo->id, msg);
	pthread_mutex_unlock(&philo->rules->end_mutex);
	pthread_mutex_unlock(&philo->rules->print_mutex);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_routine.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenlee <jenlee@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 19:49:27 by jenlee            #+#    #+#             */
/*   Updated: 2025/12/15 19:49:27 by jenlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	check_simulation_end(t_philo *philo)
{
	int	end;

	pthread_mutex_lock(&philo->rules->end_mutex);
	end = philo->rules->simulation_end;
	pthread_mutex_unlock(&philo->rules->end_mutex);
	return (end);
}

static void	init_routine_setup(t_philo *philo)
{
	wait_starting_gate(philo->rules);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = philo->rules->start_time;
	pthread_mutex_unlock(&philo->meal_mutex);
	if (philo->id % 2 == 0)
		smart_sleep(philo->rules->time_to_eat / 2, philo->rules);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->rules->nb_philo == 1)
	{
		wait_starting_gate(philo->rules);
		handle_one(philo);
		return (NULL);
	}
	init_routine_setup(philo);
	while (!check_simulation_end(philo))
	{
		eat(philo);
		print_state(philo, "is sleeping", false);
		smart_sleep(philo->rules->time_to_sleep, philo->rules);
		think_routine(philo);
	}
	return (NULL);
}

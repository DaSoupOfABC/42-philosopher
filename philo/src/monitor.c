/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenlee <jenlee@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 17:14:06 by jenlee            #+#    #+#             */
/*   Updated: 2025/12/16 17:14:06 by jenlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	check_death(t_philo *philo)
{
	long	now;
	long	last_meal;

	pthread_mutex_lock(&philo->meal_mutex);
	last_meal = philo->last_meal_time;
	pthread_mutex_unlock(&philo->meal_mutex);
	now = get_time_ms();
	if (now - last_meal > philo->rules->time_to_die)
	{
		print_state(philo, "died", true);
		return (1);
	}
	return (0);
}

static int	check_meals(t_rules *rules)
{
	int	i;
	int	full_count;

	if (rules->must_eat_count == -1)
		return (0);
	i = 0;
	full_count = 0;
	while (i < rules->nb_philo)
	{
		pthread_mutex_lock(&rules->philo[i].meal_mutex);
		if (rules->philo[i].meals_eaten >= rules->must_eat_count)
			full_count++;
		pthread_mutex_unlock(&rules->philo[i].meal_mutex);
		i++;
	}
	return (full_count == rules->nb_philo);
}

static int	scan_philosophers(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->nb_philo)
	{
		if (check_death(&rules->philo[i]))
			return (1);
		i++;
	}
	if (check_meals(rules))
	{
		pthread_mutex_lock(&rules->end_mutex);
		rules->simulation_end = true;
		pthread_mutex_unlock(&rules->end_mutex);
		return (1);
	}
	return (0);
}

static int	simulation_finished(t_rules *rules)
{
	pthread_mutex_lock(&rules->end_mutex);
	if (rules->simulation_end)
	{
		pthread_mutex_unlock(&rules->end_mutex);
		return (1);
	}
	pthread_mutex_unlock(&rules->end_mutex);
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_rules	*rules;

	rules = (t_rules *)arg;
	wait_starting_gate(rules);
	while (!simulation_finished(rules))
	{
		if (scan_philosophers(rules))
			return (NULL);
		usleep(500);
	}
	return (NULL);
}

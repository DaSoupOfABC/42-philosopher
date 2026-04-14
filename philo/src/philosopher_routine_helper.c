/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_routine_helper.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenlee <jenlee@student.42kl.edu.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 14:34:38 by jenlee            #+#    #+#             */
/*   Updated: 2026/04/14 14:58:31 by jenlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	think_routine(t_philo *philo)
{
	long	think_time;

	print_state(philo, "is thinking", false);
	if (philo->rules->nb_philo % 2 != 0)
	{
		think_time = (philo->rules->time_to_eat * 2) \
- philo->rules->time_to_sleep;
		if (think_time < 0)
			think_time = 0;
		smart_sleep(think_time + 1, philo->rules);
	}
	else
		usleep(500);
}

void	handle_one(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->mutex);
	print_state(philo, "has taken a fork", false);
	smart_sleep(philo->rules->time_to_die, philo->rules);
	pthread_mutex_unlock(&philo->left_fork->mutex);
}

void	eat(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = get_time_ms();
	pthread_mutex_unlock(&philo->meal_mutex);
	print_state(philo, "is eating", false);
	smart_sleep(philo->rules->time_to_eat, philo->rules);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
	put_forks(philo);
}

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->right_fork->mutex);
		print_state(philo, "has taken a fork", false);
		pthread_mutex_lock(&philo->left_fork->mutex);
		print_state(philo, "has taken a fork", false);
	}
	else
	{
		pthread_mutex_lock(&philo->left_fork->mutex);
		print_state(philo, "has taken a fork", false);
		pthread_mutex_lock(&philo->right_fork->mutex);
		print_state(philo, "has taken a fork", false);
	}
}

void	put_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->left_fork->mutex);
	pthread_mutex_unlock(&philo->right_fork->mutex);
}

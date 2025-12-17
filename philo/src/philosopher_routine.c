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

static void	handle_one(t_philo *philo);
static void	eat(t_philo *philo);
static void	take_forks(t_philo *philo);
static void	put_forks(t_philo *philo);

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->rules->nb_philo == 1)
	{
		handle_one(philo);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		pthread_mutex_lock(&philo->rules->end_mutex);
		if (philo->rules->simulation_end)
		{
			pthread_mutex_unlock(&philo->rules->end_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->rules->end_mutex);
		eat(philo);
		print_state(philo, "is sleeping", false);
		smart_sleep(philo->rules->time_to_sleep, philo->rules);
		print_state(philo, "is thinking", false);
	}
	return (NULL);
}

static void	eat(t_philo *philo)
{
	take_forks(philo);
	print_state(philo, "is eating", false);
	smart_sleep(philo->rules->time_to_eat, philo->rules);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = get_time_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
	put_forks(philo);
}

static void	take_forks(t_philo *philo)
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

static void	put_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->left_fork->mutex);
	pthread_mutex_unlock(&philo->right_fork->mutex);
}

static void	handle_one(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->mutex);
	print_state(philo, "has taken a fork", false);
	smart_sleep(philo->rules->time_to_die, philo->rules);
	pthread_mutex_unlock(&philo->left_fork->mutex);
}

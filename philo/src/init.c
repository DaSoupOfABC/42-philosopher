/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenlee <jenlee@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 18:57:13 by jenlee            #+#    #+#             */
/*   Updated: 2025/12/15 18:57:13 by jenlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	init_rules(t_rules *rules, char **argv, int argc)
{
	int	i;

	rules->nb_philo = ft_atoi(argv[1]);
	rules->time_to_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]);
	rules->time_to_sleep = ft_atoi(argv[4]);
	rules->must_eat_count = -1;
	if (argc == 6)
		rules->must_eat_count = ft_atoi(argv[5]);
	rules->simulation_end = false;
	rules->start_time = get_time_ms();
	if (pthread_mutex_init(&rules->print_mutex, NULL) != 0 || \
pthread_mutex_init(&rules->end_mutex, NULL) != 0)
		return (0);
	rules->fork = malloc(sizeof(t_fork) * rules->nb_philo);
	rules->philo = malloc(sizeof(t_philo) * rules->nb_philo);
	if (!rules->fork || !rules->philo)
		return (0);
	i = 0;
	while (i < rules->nb_philo)
	{
		pthread_mutex_init(&rules->fork[i].mutex, NULL);
		i++;
	}
	return (1);
}

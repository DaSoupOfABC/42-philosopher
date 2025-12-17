/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenlee <jenlee@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 17:11:46 by jenlee            #+#    #+#             */
/*   Updated: 2025/12/15 17:11:46 by jenlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	cleanup(t_rules *rules)
{
	int	i;

	if (!rules)
		return ;
	i = 0;
	while (i < rules->nb_philo)
	{
		pthread_mutex_destroy(&rules->philo[i].meal_mutex);
		pthread_mutex_destroy(&rules->fork[i].mutex);
		i++;
	}
	pthread_mutex_destroy(&rules->print_mutex);
	pthread_mutex_destroy(&rules->end_mutex);
	free(rules->fork);
	free(rules->philo);
}

int	main(int argc, char **argv)
{
	t_rules		rules;
	pthread_t	monitor;

	if (argc < 5 || argc > 6)
		return (printf("Error: wrong number of arguments\n"), 1);
	if (!validate_arguments(argv, argc))
		return (1);
	memset(&rules, 0, sizeof(t_rules));
	if (!init_rules(&rules, argv, argc))
		return (printf("Error: initialization failed\n"), 1);
	if (!init_philos(&rules))
	{
		printf("Error: philosopher initialization failed\n");
		cleanup(&rules);
		return (1);
	}
	if (!start_threads(&rules, &monitor))
	{
		printf("Error: thread creation failed\n");
		cleanup(&rules);
		return (1);
	}
	join_threads(&rules, monitor);
	cleanup(&rules);
	return (0);
}

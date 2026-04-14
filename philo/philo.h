/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenlee <jenlee@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 16:51:16 by jenlee            #+#    #+#             */
/*   Updated: 2025/12/15 16:51:16 by jenlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>
# include <string.h>

typedef struct s_rules	t_rules;

typedef struct s_fork
{
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	t_fork			*left_fork;
	t_fork			*right_fork;
	long			last_meal_time;
	int				meals_eaten;
	pthread_mutex_t	meal_mutex;
	t_rules			*rules;
}	t_philo;

typedef struct s_rules
{
	int				nb_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				must_eat_count;
	long			start_time;
	bool			simulation_end;
	bool			threads_ready;

	pthread_mutex_t	print_mutex;
	pthread_mutex_t	end_mutex;

	t_philo			*philo;
	t_fork			*fork;
}	t_rules;

/* -------- utils -------- */
int		ft_atoi(const char *str);
long	get_time_ms(void);
void	smart_sleep(long duration, t_rules *rules);

/* ---------threads-------- */
int		start_threads(t_rules *rules, pthread_t *monitor);
void	join_threads(t_rules *rules, pthread_t monitor);

/* -------- checks -------- */
int		validate_arguments(char **argv, int argc);

/* -------- init / cleanup -------- */
int		init_rules(t_rules *rules, char **argv, int argc);
void	cleanup(t_rules *rules);
int		init_philos(t_rules *rules);
void	wait_starting_gate(t_rules *rules);

/* --------simulation------ */
void	print_state(t_philo *philo, char *msg, bool is_death);
void	*philo_routine(void *arg);
void	*monitor_routine(void *arg);
void	think_routine(t_philo *philo);
void	handle_one(t_philo *philo);
void	eat(t_philo *philo);
void	take_forks(t_philo *philo);
void	put_forks(t_philo *philo);
#endif

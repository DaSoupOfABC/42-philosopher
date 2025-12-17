/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenlee <jenlee@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 17:44:18 by jenlee            #+#    #+#             */
/*   Updated: 2025/12/15 17:44:18 by jenlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	is_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+')
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	validate_arguments(char **argv, int argc)
{
	int		i;
	long	value;

	i = 1;
	while (i < argc)
	{
		if (!is_number(argv[i]))
			return (printf("Error: invalid numeric argument\n"), 0);
		value = ft_atoi(argv[i]);
		if (value <= 0)
			return (printf("Error: Does zero really exist?\n"), 0);
		i++;
	}
	return (1);
}

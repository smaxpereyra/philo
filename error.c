/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spereyra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 20:26:30 by spereyra          #+#    #+#             */
/*   Updated: 2024/07/06 16:52:18 by spereyra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_print(const char *msg, int error)
{
	printf("%s\n", msg);
	return (error);
}

void	ft_free_thread(t_arg *arg, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < arg->philo_num)
	{
		pthread_mutex_destroy(&arg->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&arg->start_mtx);
	pthread_mutex_destroy(&arg->int_mtx);
	pthread_mutex_destroy(&arg->llong_mtx);
	if (arg->forks)
		free(arg->forks);
	if (philo)
		free(philo);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spereyra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:35:10 by spereyra          #+#    #+#             */
/*   Updated: 2024/07/06 17:49:35 by spereyra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_arg_init_mutex(t_arg *arg)
{
	int	i;

	if (pthread_mutex_init(&(arg->start_mtx), NULL))
		return (1);
	if (pthread_mutex_init(&(arg->int_mtx), NULL))
		return (2);
	if (pthread_mutex_init(&(arg->llong_mtx), NULL))
		return (3);
	arg->forks = malloc(sizeof(pthread_mutex_t) * arg->philo_num);
	if (!(arg->forks))
		return (4);
	i = 0;
	while (i < arg->philo_num)
	{
		if (pthread_mutex_init(&(arg->forks[i]), NULL))
		{
			free(arg->forks);
			return (5);
		}
		i++;
	}
	return (0);
}

int	ft_arg_init(t_arg *arg, int argc, char **argv)
{
	arg->philo_num = ft_atoi(argv[1]);
	arg->time_to_die = ft_atoi(argv[2]);
	arg->time_to_eat = ft_atoi(argv[3]);
	arg->time_to_sleep = ft_atoi(argv[4]);
	arg->eat_times = 2147483647;
	if ((arg->philo_num % 2) == 1)
		arg->time_to_think = (arg->time_to_eat * 2) - arg->time_to_sleep;
	if (arg->philo_num <= 0 || arg->time_to_die < 60 \
			|| arg->time_to_eat < 60 || arg->time_to_sleep < 60)
		return (error_print("Enter at least 1 philo and 60ms timestamps", 1));
	if (argc == 6)
	{
		arg->eat_times = ft_atoi(argv[5]);
		if (arg->eat_times <= 0)
			return (error_print("Enter a number > 0 for eat_times", 2));
	}
	if (ft_arg_init_mutex(arg))
		return (3);
	return (0);
}

int	ft_philo_init(t_philo **philo, t_arg *arg)
{
	int	i;

	i = 0;
	*philo = malloc(sizeof(t_philo) * arg->philo_num);
	if (*philo == NULL)
		return (1);
	while (i < arg->philo_num)
	{
		(*philo)[i].arg = arg;
		(*philo)[i].id = i;
		if (i % 2 == 0)
		{
			(*philo)[i].left = i;
			(*philo)[i].right = (i + 1) % arg->philo_num;
		}
		else
		{
			(*philo)[i].left = (i + 1) % arg->philo_num;
			(*philo)[i].right = i;
		}
		(*philo)[i].last_eat_time = 0;
		(*philo)[i].eat_count = 0;
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_arg	arg;
	t_philo	*philo;

	philo = 0;
	if (argc != 5 && argc != 6)
		return (error_print("Required input: philos ttd tte tts [meals]", 1));
	memset(&arg, 0, sizeof(t_arg));
	if (ft_arg_init(&arg, argc, argv))
		return (2);
	if (ft_philo_init(&philo, &arg))
		return (3);
	if (ft_philo_start(&arg, philo))
		return (4);
	return (0);
}

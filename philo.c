/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spereyra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 11:40:45 by spereyra          #+#    #+#             */
/*   Updated: 2024/07/06 17:47:37 by spereyra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_philo_printf(t_arg *arg, int id, char *msg)
{
	long long	now;

	pthread_mutex_lock(&(arg->int_mtx));
	now = ft_get_time();
	if (!(arg->finish))
		printf("%lld %d %s\n", now - arg->start_time, id + 1, msg);
	pthread_mutex_unlock(&(arg->int_mtx));
}

int	ft_philo_action(t_arg *arg, t_philo *philo)
{
	pthread_mutex_lock(&(arg->forks[philo->left]));
	ft_philo_printf(arg, philo->id, "has taken a fork");
	if (arg->philo_num != 1)
	{
		pthread_mutex_lock(&(arg->forks[philo->right]));
		ft_philo_printf(arg, philo->id, "has taken a fork");
		ft_philo_printf(arg, philo->id, "is eating");
		set_longlong(&arg->llong_mtx, &philo->last_eat_time, ft_get_time());
		philo->eat_count = philo->eat_count + 1;
		ft_pass_time((long long)arg->time_to_eat, arg);
		if (arg->eat_times == philo->eat_count)
			inc_integer(&arg->int_mtx, &arg->finished_eat);
		pthread_mutex_unlock(&(arg->forks[philo->right]));
	}
	pthread_mutex_unlock(&(arg->forks[philo->left]));
	return (0);
}

void	*ft_thread(void *argv)
{
	t_arg	*arg;
	t_philo	*philo;

	philo = (t_philo *)argv;
	arg = philo->arg;
	pthread_mutex_lock(&arg->start_mtx);
	pthread_mutex_unlock(&arg->start_mtx);
	if ((philo->id % 2) == 1)
		usleep(arg->time_to_eat * 500);
	while (!is_finished(arg))
	{
		if (philo->eat_count < arg->eat_times)
			ft_philo_action(arg, philo);
		if (arg->eat_times == philo->eat_count)
			return (0);
		ft_philo_printf(arg, philo->id, "is sleeping");
		ft_pass_time((long long)arg->time_to_sleep, arg);
		ft_philo_printf(arg, philo->id, "is thinking");
		if (arg->philo_num % 2 == 1)
			ft_pass_time((long long)arg->time_to_think, arg);
	}
	return (0);
}

int	ft_philo_start(t_arg *arg, t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&arg->start_mtx);
	while (i < arg->philo_num)
	{
		philo[i].last_eat_time = ft_get_time();
		if (pthread_create(&philo[i].thread, 0, ft_thread, &philo[i]))
			return (1);
		i++;
	}
	arg->start_time = ft_get_time();
	pthread_mutex_unlock(&arg->start_mtx);
	ft_philo_check_finish(arg, philo);
	i = 0;
	while (i < arg->philo_num)
	{
		if (pthread_join(philo[i].thread, NULL))
			return (2);
		i++;
	}
	ft_free_thread(arg, philo);
	return (0);
}

void	ft_philo_check_finish(t_arg *arg, t_philo *philo)
{
	long long	now;
	int			i;

	while (!is_finished(arg))
	{
		if (arg->eat_times != 0 \
			&& arg->philo_num == get_integer(&arg->int_mtx, &arg->finished_eat))
			set_integer(&arg->int_mtx, &arg->finish, 1);
		i = 0;
		while (i < arg->philo_num && !is_finished(arg))
		{
			now = ft_get_time();
			if ((now - get_longlong(&arg->llong_mtx, &philo[i].last_eat_time)) \
				>= arg->time_to_die)
			{
				ft_philo_printf(arg, i, "died");
				set_integer(&arg->int_mtx, &arg->finish, 1);
				break ;
			}
			i++;
		}
	}
}

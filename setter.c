/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spereyra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 19:07:47 by spereyra          #+#    #+#             */
/*   Updated: 2024/07/02 19:14:17 by spereyra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	inc_integer(t_mtx *mutex, int *dest)
{
	pthread_mutex_lock(mutex);
	*dest = *dest + 1;
	pthread_mutex_unlock(mutex);
}

void	set_integer(t_mtx *mutex, int *dest, int value)
{
	pthread_mutex_lock(mutex);
	*dest = value;
	pthread_mutex_unlock(mutex);
}

void	set_longlong(t_mtx *mutex, long long *dest, long long value)
{
	pthread_mutex_lock(mutex);
	*dest = value;
	pthread_mutex_unlock(mutex);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spereyra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:35:47 by spereyra          #+#    #+#             */
/*   Updated: 2024/07/06 17:44:48 by spereyra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef pthread_mutex_t	t_mtx;

typedef struct s_arg
{
	int			philo_num;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			time_to_think;
	int			eat_times;
	long long	start_time;
	t_mtx		*forks;
	t_mtx		start_mtx;
	t_mtx		int_mtx;
	t_mtx		llong_mtx;
	int			finish;
	int			finished_eat;
}				t_arg;

typedef struct s_philo
{
	t_arg		*arg;
	pthread_t	thread;
	int			id;
	int			left;
	int			right;
	int			eat_count;
	long long	last_eat_time;
}				t_philo;

/********************************** main.c **********************************/
int			ft_arg_init_mutex(t_arg *arg);
int			ft_arg_init(t_arg *arg, int argc, char **argv);
int			ft_philo_init(t_philo **philo, t_arg *arg);

/********************************* philo.c **********************************/
void		ft_philo_printf(t_arg *arg, int id, char *msg);
int			ft_philo_action(t_arg *arg, t_philo *philo);
void		*ft_thread(void *argv);
int			ft_philo_start(t_arg *arg, t_philo *philo);
void		ft_philo_check_finish(t_arg *arg, t_philo *philo);

/********************************* time.c ***********************************/
long long	ft_get_time(void);
void		ft_pass_time(long long wait_time, t_arg *arg);

/******************************** ft_atoi.c *********************************/
int			ft_atoi(const char *str);

/******************************** setter.c **********************************/
void		inc_integer(t_mtx *mutex, int *dest);
void		set_integer(t_mtx *mutex, int *dest, int value);
void		set_longlong(t_mtx *mutex, long long *dest, long long value);

/******************************** getter.c **********************************/
int			get_integer(t_mtx *mutex, int *value);
long long	get_longlong(t_mtx *mutex, long long *value);
int			is_finished(t_arg *arg);

/******************************** error.c ***********************************/
int			error_print(const char *msg, int error);
void		ft_free_thread(t_arg *arg, t_philo *philo);

#endif

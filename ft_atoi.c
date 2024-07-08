/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spereyra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:44:08 by spereyra          #+#    #+#             */
/*   Updated: 2024/07/06 16:17:59 by spereyra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static int	ft_is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
}

static const char	*valid_input(const char *str)
{
	int			len;
	int			i;
	const char	*number;

	len = 0;
	i = 0;
	while (ft_is_space(str[i]))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
		return (NULL);
	if (!ft_is_digit(str[i]))
		return (NULL);
	number = &str[i];
	while (ft_is_digit(str[i]))
	{
		len++;
		i++;
	}
	if (len > 10)
		return (NULL);
	return (number);
}

int	ft_atoi(const char *str)
{
	long	num;
	int		i;

	num = 0;
	i = 0;
	str = valid_input(str);
	if (str == NULL)
		return (error_print("Enter only positive integer numbers!", -1));
	while (str[i] && ft_is_digit(str[i]))
	{
		num = (num * 10) + (str[i] - '0');
		i++;
	}
	if (num > 2147483647)
		return (error_print("The value is too big!", -1));
	return ((int)num);
}

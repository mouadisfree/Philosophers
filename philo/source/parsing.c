/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokatfi <mokatfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 11:35:07 by mokatfi           #+#    #+#             */
/*   Updated: 2025/07/17 00:06:26 by mokatfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/philo.h"

int	ft_is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_is_digit(*str))
	{
		result = result * 10 + (*str - '0');
		if (result * sign > INT_MAX || result * sign < INT_MIN)
			return (0);
		str++;
	}
	return (result * sign);
}

int	prog_args_init(t_prog *prog, int ac, char **av)
{
	prog->philo_count = ft_atoi(av[1]);
	prog->t_die = ft_atoi(av[2]);
	prog->t_eat = ft_atoi(av[3]);
	prog->t_sleep = ft_atoi(av[4]);
	if (ac == 6)
		prog->meals_required = ft_atoi(av[5]);
	else
		prog->meals_required = -1;
	if (prog->philo_count <= 0 || prog->t_die <= 0 || prog->t_eat <= 0
		|| prog->t_sleep <= 0 || (ac == 6 && prog->meals_required <= 0))
		return (printf("Error\n"), 1);
	return (0);
}

int	is_number(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	check_args(int ac, char **av)
{
	int	i;

	if (ac != 5 && ac != 6)
		return (printf("Error\n"), 1);
	i = 1;
	while (i < ac)
	{
		if (is_number(av[i]) == 0)
			return (printf("Error\n"), 1);
		i++;
	}
	return (0);
}

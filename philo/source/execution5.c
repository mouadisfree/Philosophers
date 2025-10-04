/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokatfi <mokatfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 11:36:13 by mokatfi           #+#    #+#             */
/*   Updated: 2025/07/17 00:12:09 by mokatfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/philo.h"

int	check_meals_count(t_philo *philo)
{
	int	enough_meals;

	enough_meals = 0;
	if (philo->prog->meals_required != -1)
	{
		pthread_mutex_lock(&philo->meal_mtx);
		if (philo->meals >= philo->prog->meals_required)
			enough_meals = 1;
		pthread_mutex_unlock(&philo->meal_mtx);
	}
	return (enough_meals);
}

int	check_if_all_ate(t_prog *prog)
{
	int	i;
	int	all_ate;

	i = -1;
	all_ate = 1;
	if (prog->meals_required == -1)
		return (0);
	while (++i < prog->philo_count)
	{
		if (!check_meals_count(&prog->philos[i]))
		{
			all_ate = 0;
			break ;
		}
	}
	return (all_ate);
}

int	is_critical_time(t_prog *prog)
{
	int	ct;

	if (prog->philo_count % 2 == 0)
		ct = (prog->t_die <= prog->t_eat + prog->t_sleep);
	else
		ct = (prog->t_die / 3 <= prog->t_eat + prog->t_sleep);
	return (ct);
}

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_usleep(long ms, t_prog *prog)
{
	long	start;

	start = get_time();
	while ((get_time() - start) < ms)
	{
		pthread_mutex_lock(&prog->dead_mtx);
		if (prog->dead)
			return ;
		pthread_mutex_unlock(&prog->dead_mtx);
		usleep(100);
	}
}

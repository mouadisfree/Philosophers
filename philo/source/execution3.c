/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokatfi <mokatfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 11:35:58 by mokatfi           #+#    #+#             */
/*   Updated: 2025/07/16 13:57:26 by mokatfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/philo.h"

void	*philo_thread(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!get_dead(philo->prog))
	{
		if (eat_action(philo))
			break ;
		if (sleep_think(philo))
			break ;
	}
	return (NULL);
}

void	*philo_thread3(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!get_dead(philo->prog))
	{
		if (eat3_action(philo))
			break ;
		if (sleep_think(philo))
			break ;
	}
	return (NULL);
}

int	create_threads(t_prog *prog)
{
	int	i;

	i = 0;
	prog->start = get_time();
	while (i < prog->philo_count)
	{
		pthread_mutex_lock(&prog->philos[i].meal_mtx);
		prog->philos[i].last_meal_time = get_time();
		pthread_mutex_unlock(&prog->philos[i].meal_mtx);
		if (prog->philo_count % 2 != 0 && i < 3)
		{
			if (pthread_create(&prog->threads[i], NULL, philo_thread3,
					&prog->philos[i]))
				return (1);
		}
		else
		{
			if (pthread_create(&prog->threads[i], NULL, philo_thread,
					&prog->philos[i]))
				return (1);
		}
		i++;
	}
	pthread_create(prog->monitor, NULL, ft_monitor, prog);
	return (0);
}

void	init_group_of_two(t_prog *prog, int start_idx)
{
	int	i;
	int	philo_idx;
	int	other_idx;

	i = 0;
	while (i < 2)
	{
		philo_idx = start_idx + i;
		other_idx = start_idx + ((i + 1) % 2);
		prog->philos[philo_idx].lfork = &prog->forks[philo_idx];
		prog->philos[philo_idx].rfork = &prog->forks[other_idx];
		i++;
	}
}

void	init_group_of_three(t_prog *prog)
{
	prog->philos[0].lfork = &prog->forks[0];
	prog->philos[0].rfork = &prog->forks[1];
	prog->philos[1].lfork = &prog->forks[1];
	prog->philos[1].rfork = &prog->forks[2];
	prog->philos[2].lfork = &prog->forks[2];
	prog->philos[2].rfork = &prog->forks[0];
}

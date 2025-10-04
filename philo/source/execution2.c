/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokatfi <mokatfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:35:53 by mokatfi           #+#    #+#             */
/*   Updated: 2025/07/16 12:50:08 by mokatfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/philo.h"

void	init_basic_data(t_prog *prog)
{
	int	i;
	int	num_philos;

	i = 0;
	num_philos = prog->philo_count;
	while (i < num_philos)
	{
		prog->philos[i].id = i;
		prog->philos[i].prog = prog;
		prog->philos[i].meals = 0;
		i++;
	}
}

void	init_groups(t_prog *prog)
{
	int	i;
	int	num_philos;

	num_philos = prog->philo_count;
	if (num_philos % 2 != 0)
	{
		init_group_of_three(prog);
		i = 3;
		while (i < num_philos)
		{
			init_group_of_two(prog, i);
			i += 2;
		}
	}
	else
	{
		i = 0;
		while (i < num_philos)
		{
			init_group_of_two(prog, i);
			i += 2;
		}
	}
}

void	philos_init(t_prog *prog)
{
	init_basic_data(prog);
	init_groups(prog);
}

int	mutexes_init(t_prog *prog)
{
	int	i;

	if (pthread_mutex_init(&prog->print_mtx, NULL)
		|| pthread_mutex_init(&prog->dead_mtx, NULL))
		return (1);
	if (prog->philo_count % 2 != 0)
		pthread_mutex_init(&prog->turn_mtx, NULL);
	i = 0;
	while (i < prog->philo_count)
	{
		if (pthread_mutex_init(&prog->forks[i], NULL)
			|| pthread_mutex_init(&prog->philos[i].meal_mtx, NULL))
		{
			while (--i >= 0)
			{
				pthread_mutex_destroy(&prog->forks[i]);
				pthread_mutex_destroy(&prog->philos[i].meal_mtx);
			}
			return (pthread_mutex_destroy(&prog->print_mtx),
				pthread_mutex_destroy(&prog->dead_mtx), 1);
		}
		i++;
	}
	return (0);
}

int	prog_init(t_prog *prog)
{
	prog->dead = 0;
	prog->forks = malloc(sizeof(pthread_mutex_t) * prog->philo_count);
	prog->threads = malloc(sizeof(pthread_t) * prog->philo_count);
	prog->monitor = malloc(sizeof(pthread_t));
	prog->philos = malloc(sizeof(t_philo) * prog->philo_count);
	if (!prog->forks || !prog->threads || !prog->monitor || !prog->philos)
	{
		if (prog->forks)
			free(prog->forks);
		if (prog->threads)
			free(prog->threads);
		if (prog->monitor)
			free(prog->monitor);
		if (prog->philos)
			free(prog->philos);
		return (1);
	}
	if (prog->philo_count % 2 != 0)
		prog->turn = 0;
	if (mutexes_init(prog))
		return (free(prog->forks), free(prog->threads), free(prog->monitor),
			free(prog->philos), 1);
	return (philos_init(prog), create_threads(prog));
}

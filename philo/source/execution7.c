/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution7.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokatfi <mokatfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 11:36:25 by mokatfi           #+#    #+#             */
/*   Updated: 2025/07/16 12:50:29 by mokatfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/philo.h"

int	eat_action(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (get_dead(philo->prog))
		return (1);
	take_forks(philo, &first_fork, &second_fork);
	if (get_dead(philo->prog))
	{
		pthread_mutex_unlock(first_fork);
		pthread_mutex_unlock(second_fork);
		return (1);
	}
	print_state(philo, "is eating");
	set_last_meal(philo);
	ft_usleep(philo->prog->t_eat, philo->prog);
	pthread_mutex_unlock(first_fork);
	pthread_mutex_unlock(second_fork);
	return (0);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n)
		i++;
	if (n == i)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	print_state(t_philo *philo, char *state)
{
	long long	current_time;

	if (!ft_strncmp(state, "died", 4))
	{
		pthread_mutex_lock(&philo->prog->print_mtx);
		current_time = get_time() - philo->prog->start;
		printf("%lld %d %s\n", current_time, philo->id + 1, state);
		pthread_mutex_unlock(&philo->prog->print_mtx);
		return ;
	}
	if (get_dead(philo->prog))
		return ;
	pthread_mutex_lock(&philo->prog->print_mtx);
	if (!get_dead(philo->prog))
	{
		current_time = get_time() - philo->prog->start;
		printf("%lld %d %s\n", current_time, philo->id + 1, state);
	}
	pthread_mutex_unlock(&philo->prog->print_mtx);
}

void	take_forks(t_philo *philo, pthread_mutex_t **first_fork,
		pthread_mutex_t **second_fork)
{
	if (philo->id % 2 == 0)
	{
		*first_fork = philo->rfork;
		*second_fork = philo->lfork;
	}
	else
	{
		*first_fork = philo->lfork;
		*second_fork = philo->rfork;
	}
	pthread_mutex_lock(*first_fork);
	print_state(philo, "has taken a fork");
	pthread_mutex_lock(*second_fork);
	print_state(philo, "has taken a fork");
}

void	prog_clean(t_prog *prog)
{
	int	i;

	if (prog->monitor)
		pthread_join(*prog->monitor, NULL);
	if (prog->threads)
	{
		i = -1;
		while (++i < prog->philo_count)
			pthread_join(prog->threads[i], NULL);
		i = -1;
		while (++i < prog->philo_count)
		{
			pthread_mutex_destroy(&prog->forks[i]);
			pthread_mutex_destroy(&prog->philos[i].meal_mtx);
		}
		pthread_mutex_destroy(&prog->print_mtx);
		pthread_mutex_destroy(&prog->dead_mtx);
		if (prog->philo_count % 2 != 0)
			pthread_mutex_destroy(&prog->turn_mtx);
		free(prog->forks);
		free(prog->threads);
		free(prog->philos);
		free(prog->monitor);
	}
}

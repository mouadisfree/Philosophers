/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokatfi <mokatfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 11:36:08 by mokatfi           #+#    #+#             */
/*   Updated: 2025/07/16 16:02:38 by mokatfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/philo.h"

int	eat3_action(t_philo *philo)
{
	if (get_dead(philo->prog))
		return (1);
	if (wait_for_turn(philo))
		return (1);
	take_forks3(philo);
	if (get_dead(philo->prog))
		return (release_resources_on_death(philo));
	print_state(philo, "is eating");
	set_last_meal(philo);
	ft_usleep(philo->prog->t_eat, philo->prog);
	pthread_mutex_unlock(philo->lfork);
	pthread_mutex_unlock(philo->rfork);
	if (!get_dead(philo->prog))
		philo->prog->turn = (philo->prog->turn + 1) % 3;
	pthread_mutex_unlock(&philo->prog->turn_mtx);
	return (0);
}

void	take_forks3(t_philo *philo)
{
	if (philo->lfork < philo->rfork)
	{
		pthread_mutex_lock(philo->lfork);
		print_state(philo, "has taken a fork");
		pthread_mutex_lock(philo->rfork);
		print_state(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->rfork);
		print_state(philo, "has taken a fork");
		pthread_mutex_lock(philo->lfork);
		print_state(philo, "has taken a fork");
	}
}

long	get_last_meal(t_philo *philo)
{
	long	last_meal_time;

	pthread_mutex_lock(&philo->meal_mtx);
	last_meal_time = philo->last_meal_time;
	pthread_mutex_unlock(&philo->meal_mtx);
	return (last_meal_time);
}

int	get_dead(t_prog *prog)
{
	int	status;

	pthread_mutex_lock(&prog->dead_mtx);
	status = prog->dead;
	pthread_mutex_unlock(&prog->dead_mtx);
	return (status);
}

void	*ft_monitor(void *arg)
{
	t_prog	*prog;
	int		i;

	prog = (t_prog *)arg;
	while (!get_dead(prog))
	{
		i = -1;
		while (++i < prog->philo_count)
		{
			if (get_time() - get_last_meal(&prog->philos[i]) >= prog->t_die)
				return (set_dead(prog->philos), print_state(&prog->philos[i],
						"died"), NULL);
		}
		if (prog->meals_required != -1 && check_if_all_ate(prog))
			return (set_dead(prog->philos), NULL);
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution6.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokatfi <mokatfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:36:20 by mokatfi           #+#    #+#             */
/*   Updated: 2025/07/16 21:04:07 by mokatfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/philo.h"

void	set_last_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mtx);
	philo->meals++;
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->meal_mtx);
}

int	wait_for_turn(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->prog->turn_mtx);
		if (philo->prog->turn == philo->id)
			break ;
		pthread_mutex_unlock(&philo->prog->turn_mtx);
		if (get_dead(philo->prog))
			return (1);
	}
	return (0);
}

int	release_resources_on_death(t_philo *philo)
{
	if (philo->lfork)
		pthread_mutex_unlock(philo->lfork);
	if (philo->rfork)
		pthread_mutex_unlock(philo->rfork);
	pthread_mutex_unlock(&philo->prog->turn_mtx);
	return (1);
}

int	sleep_think(t_philo *philo)
{
	if (get_dead(philo->prog))
		return (1);
	print_state(philo, "is sleeping");
	ft_usleep(philo->prog->t_sleep, philo->prog);
	if (get_dead(philo->prog))
		return (1);
	print_state(philo, "is thinking");
	if (get_dead(philo->prog))
		return (1);
	return (0);
}

void	set_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->prog->dead_mtx);
	philo->prog->dead = 1;
	pthread_mutex_unlock(&philo->prog->dead_mtx);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokatfi <mokatfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 11:35:16 by mokatfi           #+#    #+#             */
/*   Updated: 2025/07/16 20:45:46 by mokatfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/philo.h"

void	*one_philo(void *arg)
{
	t_prog		*prog;
	long long	start_time;

	prog = (t_prog *)arg;
	prog->start = get_time();
	start_time = get_time() - prog->start;
	printf("%lld   %d %s\n", start_time, 1, "has taken a fork");
	ft_usleep(prog->t_die, prog);
	start_time = get_time() - prog->start;
	printf("%lld %d %s\n", start_time, 1, "died");
	return (NULL);
}

int	handle_one_philo(t_prog *prog)
{
	prog->one_philo = malloc(sizeof(pthread_t));
	if (!prog->one_philo)
		return (1);
	pthread_create(prog->one_philo, NULL, one_philo, prog);
	if (prog->one_philo)
		pthread_join(*prog->one_philo, NULL);
	return (free(prog->one_philo), 0);
}

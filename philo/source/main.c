/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokatfi <mokatfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 11:34:59 by mokatfi           #+#    #+#             */
/*   Updated: 2025/07/16 14:01:13 by mokatfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/philo.h"

int	main(int ac, char **av)
{
	t_prog	program;

	if (check_args(ac, av) == 1)
		return (1);
	if (prog_args_init(&program, ac, av) == 1)
		return (1);
	if (program.philo_count == 1)
		return (handle_one_philo(&program));
	if (prog_init(&program) == 1)
		return (1);
	prog_clean(&program);
	return (0);
}

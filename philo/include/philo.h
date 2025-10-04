/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokatfi <mokatfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 20:52:40 by mokatfi           #+#    #+#             */
/*   Updated: 2025/07/17 00:04:31 by mokatfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int					id;
	int					meals;
	long long			last_meal_time;
	pthread_mutex_t		*lfork;
	pthread_mutex_t		*rfork;
	pthread_mutex_t		meal_mtx;
	struct s_prog		*prog;
}						t_philo;

typedef struct s_prog
{
	int					philo_count;
	int					t_die;
	int					t_eat;
	int					t_sleep;
	int					meals_required;
	long long			start;
	int					dead;
	pthread_mutex_t		dead_mtx;
	pthread_mutex_t		print_mtx;
	pthread_mutex_t		*forks;
	pthread_t			*threads;
	pthread_t			*monitor;
	t_philo				*philos;
	pthread_mutex_t		turn_mtx;
	pthread_t			*one_philo;
	int					turn;
}						t_prog;

void	take_forks(t_philo *philo, pthread_mutex_t **first_fork,
			pthread_mutex_t **second_fork);
int		release_resources_on_death(t_philo *philo);
int		wait_for_turn(t_philo *philo);
void	init_group_of_two(t_prog *prog, int start_idx);
int		create_threads(t_prog *prog);
int		check_if_all_ate(t_prog *prog);
int		is_number(char *str);
int		ft_atoi(const char *str);
int		handle_one_philo(t_prog *prog);
void	init_groups(t_prog *prog);
void	init_basic_data(t_prog *prog);
void	init_groups(t_prog *prog);
void	init_group_of_three(t_prog *prog);
long	get_time(void);
void	ft_usleep(long ms, t_prog *prog);
int		is_critical_time(t_prog *prog);
void	print_state(t_philo *philo, char *state);
int		get_dead(t_prog *prog);
void	set_dead(t_philo *philo);
long	get_last_meal(t_philo *philo);
void	set_last_meal(t_philo *philo);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		check_args(int ac, char **av);
int		prog_args_init(t_prog *prog, int ac, char **av);
void	*ft_monitor(void *arg);
int		prog_init(t_prog *prog);
int		mutexes_init(t_prog *prog);
void	philos_init(t_prog *prog);
void	take_forks3(t_philo *philo);
int		eat_action(t_philo *philo);
int		eat3_action(t_philo *philo);
int		sleep_think(t_philo *philo);
void	*philo_thread(void *arg);
void	*philo_thread3(void *arg);
void	prog_clean(t_prog *prog);
#endif

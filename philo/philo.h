/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-yous <jel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 20:31:24 by jel-yous          #+#    #+#             */
/*   Updated: 2025/09/21 20:43:21 by jel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

# define DEAD 1
# define ALIVE 2

typedef struct s_table
{
	int				is_all_eatean;
	int				is_dead;
	int				table_size;
	long			time_to_eat;
	long			time_to_sleep;
	long			time_to_die;
	long			number_of_meals;
	long long		start_time;
	int				*full_check;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	full_mutex;
}	t_table;

typedef struct s_philo
{
	int				id;
	int				eat_count;
	long long		last_eat_time;
	int				is_full;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	meal_mutex;
	t_table			*table;
}	t_philo;

long			ft_atol(char *s, int *err);
long long		ft_gettime(void);
void			ft_usleep(long long time, t_table *table);

void			destroy_table_mutexes(t_table *t);
void			destroy_forks_mutexes(pthread_mutex_t *f, int size);
void			clean_all(t_table *t, t_philo *p, pthread_mutex_t *f);

void			*routine(void *a);
void			monitor(t_philo *p, t_table *t);

t_table			*init_table(int ac, char **av);
t_philo			*init_philos(t_table *t, pthread_mutex_t *f);
pthread_mutex_t	*init_forks(t_table *t);
void			join_threads_philo(t_philo *p, int size);

void			ft_printf(char *s, t_philo *p, int flag);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table_forks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-yous <jel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 20:31:14 by jel-yous          #+#    #+#             */
/*   Updated: 2025/09/21 20:36:38 by jel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_table_mutexes(t_table *t)
{
	if (pthread_mutex_init(&t->death_mutex, NULL) != 0)
	{
		return (0);
	}
	if (pthread_mutex_init(&t->full_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&t->death_mutex);
		return (0);
	}
	if (pthread_mutex_init(&t->print_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&t->death_mutex);
		pthread_mutex_destroy(&t->full_mutex);
		return (0);
	}
	return (1);
}

pthread_mutex_t	*init_forks(t_table *t)
{
	pthread_mutex_t	*f;
	int				i;

	f = malloc(sizeof(pthread_mutex_t) * t->table_size);
	if (!f)
	{
		return (NULL);
	}
	i = 0;
	while (i < t->table_size)
	{
		if (pthread_mutex_init(&f[i], NULL) != 0)
		{
			while (--i >= 0)
			{
				pthread_mutex_destroy(&f[i]);
			}
			free(f);
			return (NULL);
		}
		i++;
	}
	return (f);
}

void	init_table_data(int ac, char **av, t_table *t, int *err)
{
	t->table_size = ft_atol(av[1], err);
	t->time_to_die = ft_atol(av[2], err);
	t->time_to_eat = ft_atol(av[3], err);
	t->time_to_sleep = ft_atol(av[4], err);
	if (ac == 6)
		t->number_of_meals = ft_atol(av[5], err);
	else
		t->number_of_meals = -1;
	t->is_all_eatean = 0;
	t->start_time = ft_gettime();
	t->is_dead = 0;
}

t_table	*init_table(int ac, char **av)
{
	t_table	*t;
	int		err;

	err = 0;
	t = malloc(sizeof(t_table));
	if (!t)
		return (NULL);
	init_table_data(ac, av, t, &err);
	if (err == -1)
	{
		free(t);
		printf("Error: invalid arguments\n");
		return (NULL);
	}
	if (!init_table_mutexes(t))
	{
		free(t);
		return (NULL);
	}
	return (t);
}

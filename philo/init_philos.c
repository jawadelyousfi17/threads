/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-yous <jel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 20:31:08 by jel-yous          #+#    #+#             */
/*   Updated: 2025/09/21 21:10:41 by jel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_single_philo(t_philo *p, t_table *t, int i, pthread_mutex_t *f)
{
	p[i].id = i + 1;
	p[i].is_full = 0;
	p[i].last_eat_time = ft_gettime();
	p[i].eat_count = 0;
	p[i].table = t;
	p[i].left_fork = &f[i];
	p[i].right_fork = &f[(i + 1) % t->table_size];
	if (pthread_mutex_init(&p[i].meal_mutex, NULL) != 0)
	{
		while (--i >= 0)
		{
			pthread_mutex_destroy(&p[i].meal_mutex);
			pthread_join(p[i].thread, NULL);
		}
		return (0);
	}
	return (1);
}

int	init_philo_create_tread(t_philo *p, int i)
{
	if (pthread_create(&p[i].thread, NULL, routine, &p[i]) != 0)
	{
		pthread_mutex_destroy(&p[i].meal_mutex);
		while (--i >= 0)
		{
			pthread_join(p[i].thread, NULL);
			pthread_mutex_destroy(&p[i].meal_mutex);
		}
		return (0);
	}
	return (1);
}

void	join_threads_philo(t_philo *p, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		pthread_join(p[i].thread, NULL);
		i++;
	}
}

t_philo	*init_philos(t_table *t, pthread_mutex_t *f)
{
	t_philo	*p;
	int		i;

	p = malloc(sizeof(t_philo) * t->table_size);
	if (!p)
	{
		return (NULL);
	}
	i = 0;
	while (i < t->table_size)
	{
		if (!init_single_philo(p, t, i, f) || !init_philo_create_tread(p, i))
		{
			free(p);
			return (NULL);
		}
		i++;
	}
	return (p);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-yous <jel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 20:31:21 by jel-yous          #+#    #+#             */
/*   Updated: 2025/09/21 20:39:17 by jel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	stats(t_philo *p, t_table *t)
{
	pthread_mutex_lock(p->left_fork);
	ft_printf("has taken a fork", p, ALIVE);
	if (t->table_size == 1)
	{
		pthread_mutex_unlock(p->left_fork);
		return (0);
	}
	pthread_mutex_lock(p->right_fork);
	ft_printf("has taken a fork", p, ALIVE);
	ft_printf("is eating", p, ALIVE);
	pthread_mutex_lock(&p->meal_mutex);
	p->last_eat_time = ft_gettime();
	p->eat_count++;
	pthread_mutex_unlock(&p->meal_mutex);
	ft_usleep(t->time_to_eat, t);
	pthread_mutex_unlock(p->left_fork);
	pthread_mutex_unlock(p->right_fork);
	ft_printf("is sleeping", p, ALIVE);
	ft_usleep(t->time_to_sleep, t);
	ft_printf("is thinking", p, ALIVE);
	return (1);
}

int	death_full_check(t_table *t, t_philo *p)
{
	pthread_mutex_lock(&t->death_mutex);
	if (t->is_dead)
		return (pthread_mutex_unlock(&t->death_mutex), 0);
	pthread_mutex_unlock(&t->death_mutex);
	pthread_mutex_lock(&p->meal_mutex);
	if (p->eat_count == t->number_of_meals)
	{
		p->is_full = 1;
		pthread_mutex_unlock(&p->meal_mutex);
		return (0);
	}
	pthread_mutex_unlock(&p->meal_mutex);
	return (1);
}

void	*routine(void *a)
{
	t_philo	*p;
	t_table	*t;

	p = (t_philo *)a;
	t = p->table;
	if (p->id % 2 == 0)
		usleep(100);
	while (1)
	{
		if (!death_full_check(t, p))
			return (NULL);
		if (!stats(p, t))
			return (NULL);
	}
}

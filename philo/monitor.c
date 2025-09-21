/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-yous <jel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 20:31:19 by jel-yous          #+#    #+#             */
/*   Updated: 2025/09/21 20:39:19 by jel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	monitor_util(t_philo *p, t_table *t, int *is_all_full, int i)
{
	pthread_mutex_lock(&p[i].meal_mutex);
	if (ft_gettime() - p[i].last_eat_time > t->time_to_die)
	{
		pthread_mutex_lock(&t->death_mutex);
		t->is_dead = 1;
		ft_printf("died", &p[i], DEAD);
		pthread_mutex_unlock(&t->death_mutex);
		pthread_mutex_unlock(&p[i].meal_mutex);
		return (0);
	}
	if (p[i].eat_count == t->number_of_meals)
		*is_all_full = *is_all_full + 1;
	pthread_mutex_unlock(&p[i].meal_mutex);
	return (1);
}

void	monitor(t_philo *p, t_table *t)
{
	int	i;
	int	is_all_full;

	while (1)
	{
		is_all_full = 0;
		i = 0;
		while (i < t->table_size)
		{
			if (!monitor_util(p, t, &is_all_full, i))
				return ;
			i++;
		}
		if (is_all_full == t->table_size)
		{
			pthread_mutex_lock(&t->full_mutex);
			t->is_all_eatean = 1;
			pthread_mutex_unlock(&t->full_mutex);
		}
		usleep(100);
	}
}

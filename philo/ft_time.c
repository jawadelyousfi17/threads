/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-yous <jel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 20:31:06 by jel-yous          #+#    #+#             */
/*   Updated: 2025/09/21 20:42:45 by jel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_gettime(void)
{
	struct timeval	v;
	long long		time;

	gettimeofday(&v, NULL);
	time = (v.tv_sec * 1000) + (v.tv_usec / 1000);
	return (time);
}

void	ft_usleep(long long time, t_table *t)
{
	long long	start;

	start = ft_gettime();
	while ((ft_gettime() - start) < time)
	{
		pthread_mutex_lock(&t->death_mutex);
		if (t->is_dead)
		{
			pthread_mutex_unlock(&t->death_mutex);
			return ;
		}
		pthread_mutex_unlock(&t->death_mutex);
		usleep(100);
	}
	return ;
}

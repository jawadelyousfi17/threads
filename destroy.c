/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-yous <jel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 20:30:58 by jel-yous          #+#    #+#             */
/*   Updated: 2025/09/21 20:34:46 by jel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_table_mutexes(t_table *t)
{
	pthread_mutex_destroy(&t->death_mutex);
	pthread_mutex_destroy(&t->full_mutex);
	pthread_mutex_destroy(&t->print_mutex);
}

void	destroy_forks_mutexes(pthread_mutex_t *f, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		pthread_mutex_destroy(&f[i]);
		i++;
	}
}

void	clean_all(t_table *t, t_philo *p, pthread_mutex_t *f)
{
	int	i;

	i = 0;
	while (i < t->table_size)
	{
		pthread_mutex_destroy(&f[i]);
		pthread_mutex_destroy(&p[i].meal_mutex);
		i++;
	}
	destroy_table_mutexes(t);
	free(t);
	free(f);
	free(p);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-yous <jel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 20:31:17 by jel-yous          #+#    #+#             */
/*   Updated: 2025/09/21 21:15:40 by jel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	destroy_util(t_table *t, pthread_mutex_t *f)
{
	destroy_table_mutexes(t);
	free(t);
	destroy_forks_mutexes(f, t->table_size);
	free(f);
	return (1);
}

int	main(int ac, char **av)
{
	t_table			*t;
	t_philo			*p;
	pthread_mutex_t	*f;

	if (ac != 5 && ac != 6)
	{
		printf("Error: invalid arguments\n");
		return (1);
	}
	t = init_table(ac, av);
	if (!t)
		return (1);
	f = init_forks(t);
	if (!f)
		return (destroy_table_mutexes(t), free(t), 1);
	p = init_philos(t, f);
	if (!p)
		return (destroy_util(t, f));
	monitor(p, t);
	join_threads_philo(p, t->table_size);
	clean_all(t, p, f);
	return (0);
}

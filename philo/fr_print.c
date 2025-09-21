/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fr_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-yous <jel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 20:31:01 by jel-yous          #+#    #+#             */
/*   Updated: 2025/09/21 21:10:07 by jel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_mtx(t_table *t)
{
	pthread_mutex_lock(&t->full_mutex);
	if (t->is_all_eatean)
	{
		pthread_mutex_unlock(&t->full_mutex);
		return (0);
	}
	pthread_mutex_unlock(&t->full_mutex);
	return (1);
}

void	ft_printf(char *s, t_philo *p, int flag)
{
	t_table		*t;
	long long	time;
	static int	status;

	t = p->table;
	time = ft_gettime() - t->start_time;
	if (!print_mtx(t))
		return ;
	pthread_mutex_lock(&t->print_mutex);
	if (flag == DEAD)
	{
		printf("%lld %d %s\n", time, p->id, s);
		status = 1;
		pthread_mutex_unlock(&t->print_mutex);
		return ;
	}
	if (status)
	{
		pthread_mutex_unlock(&t->print_mutex);
		return ;
	}
	printf("%lld %d %s\n", time, p->id, s);
	pthread_mutex_unlock(&t->print_mutex);
}

#include "philo.h"

int stats(t_philo *p, t_table *t)
{

    pthread_mutex_t *first_fork;
    pthread_mutex_t *second_fork;
    if (p->left_fork < p->right_fork)
    {
        first_fork = p->left_fork;
        second_fork = p->right_fork;
    }
    else
    {
        first_fork = p->right_fork;
        second_fork = p->left_fork;
    }
    LOCK(first_fork);
    ft_printf("has taken a fork", p, ALIVE);
    if (t->table_size == 1)
    {
        UNLOCK(first_fork);
        return 0;
    }
    LOCK(second_fork);
    ft_printf("has taken a fork", p, ALIVE);
    ft_printf("is eating", p, ALIVE);
    LOCK(&p->meal_mutex);
    p->last_eat_time = ft_gettime();
    p->eat_count++;
    UNLOCK(&p->meal_mutex);
    ft_usleep(t->time_to_eat, t);
    UNLOCK(first_fork);
    UNLOCK(second_fork);
    ft_printf("is sleeping", p, ALIVE);
    ft_usleep(t->time_to_sleep, t);
    ft_printf("is thinking", p, ALIVE);
    return 1;
}

int death_full_check(t_table *t, t_philo *p)
{
    LOCK(&t->death_mutex);
    if (t->is_dead)
        return (UNLOCK(&t->death_mutex), 0);
    UNLOCK(&t->death_mutex);
    LOCK(&p->meal_mutex);
    if (p->eat_count == t->number_of_meals)
    {
        p->is_full = 1;
        UNLOCK(&p->meal_mutex);
        return 0;
    }
    UNLOCK(&p->meal_mutex);
    return 1;
}

void *routine(void *a)
{
    t_philo *p;
    t_table *t;

    p = (t_philo *)a;
    t = p->table;
    if (p->id % 2 == 0)
        usleep(100);
    while (1)
    {
        if (!death_full_check(t, p))
            return NULL;
        if (!stats(p, t))
            return NULL;
    }
}

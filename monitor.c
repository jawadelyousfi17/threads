#include "philo.h"

void monitor(t_philo *p, t_table *t)
{
    int i;
    int is_all_full;

    while (1)
    {
        is_all_full = 0;
        i = 0;
        while (i < t->table_size)
        {
            LOCK(&p[i].meal_mutex);
            if (ft_gettime() - p[i].last_eat_time > t->time_to_die)
            {
                LOCK(&t->death_mutex);
                t->is_dead = 1;
                ft_printf("died", &p[i], DEAD);
                UNLOCK(&t->death_mutex);
                UNLOCK(&p[i].meal_mutex);
                return;
            }
            if (p[i].eat_count == t->number_of_meals)
            {
                is_all_full++;
            }
            UNLOCK(&p[i].meal_mutex);
            i++;
        }
        if (is_all_full == t->table_size)
        {
            LOCK(&t->full_mutex);
            t->is_all_eatean = 1;
            UNLOCK(&t->full_mutex);
        }
        usleep(100);
    }
}


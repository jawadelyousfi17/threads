#include "philo.h"

long long ft_gettime(void)
{
    struct timeval v;
    long long time;

    gettimeofday(&v, NULL);
    time = (v.tv_sec * 1000) + (v.tv_usec / 1000);
    return (time);
}

void ft_usleep(long long time, t_table *t)
{
    long long start;

    start = ft_gettime();
    while ((ft_gettime() - start) < time)
    {
        LOCK(&t->death_mutex);
        if (t->is_dead)
        {
            UNLOCK(&t->death_mutex);
            return;
        }
        UNLOCK(&t->death_mutex);
        usleep(100);
    }
    return;
}
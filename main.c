#include "philo.h"

int destroy_util(t_table *t, t_philo *p, pthread_mutex_t *f)
{
    destroy_table_mutexes(t);
    free(t);
    destroy_forks_mutexes(f, t->table_size);
    free(f);
    return 1;
}

int main(int ac, char **av)
{
    t_table *t;
    t_philo *p;
    pthread_mutex_t *f;

    if (ac != 5 && ac != 6)
        return 1;
    t = init_table(ac, av);
    if (!t)
        return 1;
    f = init_forks(t);
    if (!f)
        return (destroy_table_mutexes(t), free(t), 1);
    p = init_philos(t, f);
    if (!p)
        return destroy_util(t, p, f);
    monitor(p, t);
    join_threads_philo(p, t->table_size);
    clean_all(t, p, f);
    return 0;
}

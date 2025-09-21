#include "philo.h"

int print_mtx(t_table *t)
{
  LOCK(&t->full_mutex);
    if (t->is_all_eatean)
    {

        UNLOCK(&t->full_mutex);
        return 0;
    }
    UNLOCK(&t->full_mutex);
    return 1;
}

void ft_printf(char *s, t_philo *p, int flag)
{
    t_table *t;
    long long time;
    static int status;

    t = p->table;
    time = ft_gettime() - t->start_time;
    if (!print_mtx(t))
        return;
    LOCK(&t->print_mutex);
    if (flag == DEAD)
    {
        printf("%lld %d %s\n", time, p->id, s);
        status = 1;
        UNLOCK(&t->print_mutex);
        return;
    }
    if (status)
    {
        UNLOCK(&t->print_mutex);
        return;
    }
    printf("%lld %d %s\n", time, p->id, s);
    UNLOCK(&t->print_mutex);
}

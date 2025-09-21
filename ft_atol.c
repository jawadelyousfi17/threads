#include "philo.h"


long	ft_atol(char *s, int *err)
{
    long    	res;
    int			i;

    *err = 0;
    i = 0;
    res = 0;
    while (*s == ' ' || (*s == '\t'))
        s++;
    if (*s == '+' || *s == '-')
    {
        if (*s++ == '-')
            *err = -1;
    }
    if (!*s)
        return (*err = -1, 0);
    while (*s >= '0' && *s <= '9')
    {
        res = (res * 10) + (*s - '0');
        s++;
    }
    if (*s != '\0')
        return (*err = -1, 0); 
    return ((long)(res));
}

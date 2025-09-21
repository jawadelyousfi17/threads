#include "philo.h"

long	ft_atol(char *s, int *err)
{
    long long	res;
    int			i;
    int			sign;

    *err = 0;
    i = 0;
    sign = 1;
    res = 0;
    while (s[i] == ' ' || (s[i] >= '\t' && s[i] <= '\r'))
        i++;
    if (s[i] == '+' || s[i] == '-')
    {
        if (s[i] == '-')
            sign = -1;
        i++;
    }
    if (!s[i])
        return (*err = -1, (long)0);
    while (s[i] >= '0' && s[i] <= '9')
    {
        res = (res * 10) + (s[i] - '0');
        i++;
    }
    if (s[i] != '\0')
        return (*err = -1, (long)0);
    if (res <= 0 || sign == -1)
        *err = -1; 
    return ((long)(res * sign));
}
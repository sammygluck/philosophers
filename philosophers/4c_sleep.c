#include "philosophers.h"

long long time_now(void)
{
    t_timeval now;
    long long now_ms;

    gettimeofday(&now, NULL);
    now_ms = ((long long)now.tv_sec *1000) + (now.tv_usec / 1000);
    return (now_ms);
}

//it can be more fair to split up the sleeping sessions
void philo_sleep(t_philo *philo)
{
    long microseconds;
    
    log_action(philo, "sleeping");
    microseconds = philo->data->time_to_sleep * 1000;
    usleep(microseconds);
}
#include "philosophers.h"

void pick_up_forks(t_philo *philo)
{
    if (philo->id == philo->data->philo_nr)
    {
        //error-notes
        pthread_mutex_lock(philo->right_fork);
        log_action(philo, "has taken a fork");
        pthread_mutex_lock(philo->left_fork);
        log_action(philo, "has taken a fork");
    }
    else
    {
        //error-notes
        pthread_mutex_lock(philo->left_fork);
        log_action(philo, "has taken a fork");
        pthread_mutex_lock(philo->right_fork);
        log_action(philo, "has taken a fork");
    }
}

void put_forks_down(t_philo *philo)
{
    //error-notes
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
}

void philo_eat(t_philo *philo)
{
    //check if need to still eat
    //if there is only one philo => starve and die; location note
    pick_up_forks(philo);
    log_action(philo, "is eating");
    usleep(philo->data->time_to_eat * 1000);
    put_forks_down(philo);
    philo->last_eat = time_now(void);
    philo->eat_count += 1;
}
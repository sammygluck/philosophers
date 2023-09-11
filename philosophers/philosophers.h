#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct timeval t_timeval;
typedef struct data {
    int philo_nr;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int max_eats;
    int all_alive;
    long long start_routine;
    pthread_mutex_t log_mutex; 
    pthread_mutex_t **fork_mutexes;
    pthread_mutex_t alive_mutex;
} t_data;

typedef struct s_philo {
    int id; 
    int eat_count;
    long long last_eat;
    pthread_t tid;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    pthread_mutex_t last_meal_mtx;
    pthread_mutex_t eat_count_mtx;
    t_data *data;
    
} t_philo;


void init_data(t_data *data, int argc, char **argv);
int	ft_atoi(const char *str);
int is_str_all_digit(char *str);
int ft_is_digit(int c);
void init_philos(t_philo ***philos, t_data *data);
void init_mutexes(t_data *data);
void set_philo_mutex(t_philo ***philosophers, t_data *data);
void run_philos(t_philo ***philosophers, t_data *data);
void *think_eat_sleep(void *arg);
void log_action(t_philo *philo, char *str);
void philo_think(t_philo *philo);
int philo_eat(t_philo *philo);
void put_forks_down(t_philo *philo);
void pick_up_forks(t_philo *philo);
void lonely_philo(t_philo *philo);
void philo_sleep(t_philo *philo);
void optimized_sleep(int to_sleep);
long long time_now(void);
void	*monitor(void *philosophers);
int	check_philos_status(t_philo **philos);
int	check_if_died(t_philo *philos);
int all_eaten(t_philo **philos);


#endif
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
    pthread_mutex_t *log_mutex; //still needs to be initialized
    pthread_mutex_t **fork_mutexes;
} t_data;
typedef struct s_philo {
    int id;
    pthread_t tid;
    int eat_count;
    int max_eats;
    t_data *data;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    //thread id
    //forks
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
void philo_eat(t_philo *philo);
void put_forks_down(t_philo *philo);
void pick_up_forks(t_philo *philo);
void philo_sleep(t_philo *philo);
long long time_now(void);


#endif
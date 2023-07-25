#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <pthread.h>

typedef struct data {
    int philo_nr;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int max_eats;
} t_data;
typedef struct s_philo {
    int id;
    int eat_count;
    int max_eats;
    //thread id
    //forks
} t_philo;


void init_data(t_data *data, int argc, char **argv);
int	ft_atoi(const char *str);
int ft_is_digit(int c);
int is_str_all_digit(char *str);
void init_philos(t_philo ***philosophers, t_data data);


#endif
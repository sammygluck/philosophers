#include "philosophers.h"

void print_philos(t_philo **philosophers, int count)
{
    int i;

    i = 0;
    while (i < count)
    {
        //note
        printf("%i\n", philosophers[i]->id);
        i++;
    }
}

int main(int argc, char **argv)
{
    t_data data;
    t_philo **philosophers;

    philosophers = NULL;
    init_data(&data, argc, argv);
    init_philos(&philosophers, &data);
    run_philos(&philosophers, &data);
    //print_philos(philosophers, data.philo_nr);
}

// //original testing code
// int i = 2;

// void *test(void *p)
// {
//     printf("Value is %i\n", *(int *)p);

//     pthread_exit(&i);
// }

// int main(void)
// {
//     pthread_t id;
//     int j;
//     int *ptr;

//     j = 1;
//     (void) argc;
//     (void) argv;
//     pthread_create(&id, NULL, test, &j);
//     pthread_join(id, (void **)&ptr);
//     printf("Value received by parent from child: ");
//     printf("%i\n", *ptr);
// }
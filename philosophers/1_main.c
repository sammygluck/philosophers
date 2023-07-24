#include "philosophers.h"

int main(int argc, char **argv)
{
    t_data data;
    t_philo **philosophers;

    init_data(&data);
    init_philos(philosophers, data);
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
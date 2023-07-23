#include "philosophers.h"

int i = 2;

void *test(void *parameter)
{
    printf("Value is %i\n", *(int *)p);

    pthread_exit(&i);
}

int main(void)
{
    pthread_t id;
    int j;

    j = 1;
    pthread_create(&id, NULL, test, &j);
    pthread_join(id, (void **)&ptr);
    printf("Value received by parent from chilld: ");
    printf("%i\n", *ptr);
}
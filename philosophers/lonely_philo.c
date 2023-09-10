#include "philosophers.h"

/*
We would like to find a way to deal with lonely philo.
Why not integrate this function in the general program.
One single reason: the print action. I don't want to have a double printing event.
The question is, can we integrate the double logging prevention inside our function?
Maybe we can: we will check if there are more than 1 philo before we log that a philo has died.
*/
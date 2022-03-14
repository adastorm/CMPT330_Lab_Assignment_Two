#include "ChocolateFactory.h"

void *oompa_loompa_thread(void *tid)
{
    for (int i = 0; i < candiesPerOompa; i++)
    {
        //print the status
        printf("[ %s ]\t: %d \n", *colors[(int)(long)tid], i);

        
        // Add the details to the struct and push to teh stack
    }
    pthread_exit(NULL);
    return NULL;
}
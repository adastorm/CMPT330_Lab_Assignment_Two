/*
Jonah Watts
2002006
CMPT330
*/

#include "ChocolateFactory.h"

void *oompa_loompa_thread(void *tid)
{
    //Loop for the amount of candies to produce
    for (int i = 0; i < candiesPerOompa; i++)
    {
        //Lock the mutex
        pthread_mutex_lock(&lock);
        //print the status
        printf("[ Oompa Loompa %d ]\t:%s %d \n", (int)(long)tid, *colors[(int)(long)tid], i);

        // Add the details to the struct and push to teh stack
        struct candy temp;
        temp.flavor = (int)(long)tid % 26;
        temp.loop = (int)(long)tid / 26;
        temp.number = i;

        //Sleep if the conveyor is full
        while(conveyorSize==candiesInConveyor)
            pthread_cond_wait(&condO, &lock);
        
        //Incriment and then add to the list
        candiesInConveyor++;
        list[oompaPosition] = temp;
        oompaPosition++;
        if (oompaPosition >= conveyorSize)
            oompaPosition = 0;

        //Release and unlock mutex
        pthread_cond_broadcast(&condC);
        pthread_mutex_unlock(&lock);
    }

    printf("\n[ Oompa Loompa ] EXITING THREAD %d\n", (int)(long)tid);
    pthread_exit(NULL);
    return NULL;
}
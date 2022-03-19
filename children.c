/*
Jonah Watts
2002006
CMPT330
*/

#include "ChocolateFactory.h"

void *child_thread(void *tid)
{

    // print the status
    printf("[ I am Child #%d ]\t: space for %i candies per box\n", (int)(long)tid,candiesPerBox);

    struct candy *box = malloc(candiesPerBox * sizeof(box));
    int candies_in_box = 0;
    while (isDoneProduction == 1 || candiesInConveyor > 0)
    {
        // Lock Mutex
        pthread_mutex_lock(&lock);
        // printf("And i locked the mutex and isDoneProduction=%d and candiesInConveyor=%d\n",isDoneProduction,candiesInConveyor);
        //Wait if there is not enough space
        while (candiesInConveyor <= 0 && isDoneProduction == 1)
        {
            pthread_cond_wait(&condC, &lock);
        }
        // printf("waiting");
        if (candiesInConveyor > 0)
        {

            struct candy temp = list[childPosition];
            box[candies_in_box] = temp;
            candiesInConveyor--;
            childPosition++;
            if (childPosition >= conveyorSize)
                childPosition = 0;
            candies_in_box++;
        }

        //Empty the box if its full
        if(candies_in_box == candiesPerBox)
        {
            printf("[ Child Thread %d ]\tWonka, I have a box of candies conataining: ", (int)(long)tid);
            for (int i = 0; i < candiesPerBox;i++)
            {
                printf("%s %d ",*colors[box[i].flavor], box[i].number);
            }
            printf("\n");
            candies_in_box = 0;
            box = realloc(box, candiesPerBox * sizeof(box));
        }

        pthread_cond_broadcast(&condO);
        pthread_mutex_unlock(&lock);
        
    }
    // free(box);
    printf("[ Child ] EXITING THREAD % d\n", (int)(long)tid);
    pthread_exit(NULL);
    return NULL;
}
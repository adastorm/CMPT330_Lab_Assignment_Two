#include "ChocolateFactory.h"

void *child_thread(void *tid)
{

    // print the status
    printf("[ I am Child #%d ]\t: space for %i candies per box\n", (int)(long)tid,candiesPerBox);

    pthread_exit(NULL);
    return NULL;
}
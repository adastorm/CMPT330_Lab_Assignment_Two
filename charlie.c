#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

void *print_hello_world(void *tid)
{
    printf("[ THREAD %d ]\t: Hello World!\n", (int)(long)tid);
    pthread_exit(NULL);
    return NULL;
}

int main(int argc, const char *argv[])
{
    //First check is there are enogh command line arguments 
    if (argc != 6){
        printf("Fail\n");
        exit(EXIT_FAILURE);
    }

    // Take in teh command line arguments
    int NumOmpaLoopmpas = atoi(argv[1]);
    int NumChildren     = atoi(argv[2]);
    int conveyorSize    = atoi(argv[3]);
    int candiesPerBox   = atoi(argv[4]);
    int candiesPerOompa = atoi(argv[5]);

    printf("Loompas: %d Children: %d  Conveyor: %d BoxSize: %d Candies per LOompa: %d\n", NumOmpaLoopmpas, NumChildren, conveyorSize, candiesPerBox, candiesPerOompa);

    //Create arrays for the threads
    pthread_t oompaLoompas[NumOmpaLoopmpas];
    pthread_t children[NumChildren];

    int status, i;

    //Generate child threads
    for (i = 0; i < NumChildren; i++)
    {
        printf("[ MAIN ]      \t: Creating %d\n", i);
        status = pthread_create(&children[i], NULL, print_hello_world, (void *)(long)i);
        if (status != 0)
        {
            printf("Oops, pthread_create returned error code %d\n", status);
            exit(EXIT_FAILURE);
        }
    }

    //Generate Oompa loompa threads
    for (i = 0; i < NumOmpaLoopmpas; i++)
    {
        printf("[ MAIN ]      \t: Creating %d\n", i);
        status = pthread_create(&oompaLoompas[i], NULL, print_hello_world, (void *)(long)i);
        if (status != 0)
        {
            printf("Oops, pthread_create returned error code %d\n", status);
            exit(EXIT_FAILURE);
        }
    }
    for (i = 0; i < NumChildren; i++)
        pthread_join(children[i], NULL);
    for (i = 0; i < NumOmpaLoopmpas; i++)
        pthread_join(oompaLoompas[i],NULL);

    exit(EXIT_SUCCESS);
}
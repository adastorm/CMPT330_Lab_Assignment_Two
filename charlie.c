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
    if (argc != 6){
        printf("Fail\n");
        exit(EXIT_FAILURE);
    }

    int NumOmpaLoopmpas = argv[1];
    int NumChildren     = argv[2];
    int conveyorSize    = argv[3];
    int candiesPerBox   = argv[4];
    int candiesPerOompa = argv[5];

    pthread_t oompaLoompas[NumOmpaLoopmpas];
    pthread_t children[NumChildren];

    int status, i;

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
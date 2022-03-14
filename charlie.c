#include "ChocolateFactory.h"


//Initialize the variables needed for teh command line arguments
int NumOmpaLoopmpas;
int NumChildren;
int conveyorSize;
int candiesPerBox;
int candiesPerOompa;

//Keep Track of Candies in conveyor
int candiesInConveyor;
int oompaPosition;
int childPosition;
struct candy *list;

void createConveyor(){
    //initialize the data and the array
    candiesInConveyor = 0;
    oompaPosition = 0;
    childPosition = 0;
    list = malloc(conveyorSize*sizeof(*list));
}
int addToConveyor(struct candy input){
    if(conveyorSize = candiesInConveyor)
        return 0;
    else{
        list[oompaPosition] = input;
        oompaPosition++;
        if (oompaPosition >= conveyorSize)
            oompaPosition = 0;
    }
}

struct candy removeFromConveyor(){
    //If there is candy to be removed, remove the candy
    //Decriment the amount of candies
    //Return the cnady
}



//The main Thread
int main(int argc, const char *argv[])
{
    
    // First check is there are enogh command line arguments
    if (argc != 6){
        printf("Fail\n");
        exit(EXIT_FAILURE);
    }

    // Take in the command line arguments
    NumOmpaLoopmpas = atoi(argv[1]);
    NumChildren     = atoi(argv[2]);
    conveyorSize    = atoi(argv[3]);
    candiesPerBox   = atoi(argv[4]);
    candiesPerOompa = atoi(argv[5]);

    //Create circular queue
    int conveyorBelt[conveyorSize];

    printf("Loompas: %d Children: %d  Conveyor: %d BoxSize: %d Candies per LOompa: %d\n", NumOmpaLoopmpas, NumChildren, conveyorSize, candiesPerBox, candiesPerOompa);

    //Create arrays for the threads
    pthread_t oompaLoompas[NumOmpaLoopmpas];
    pthread_t children[NumChildren];

    int status, i;

    //Generate child threads
    for (i = 0; i < NumChildren; i++)
    {
        printf("[ MAIN ]      \t: Creating Child %d\n", i);
        status = pthread_create(&children[i], NULL, child_thread, (void *)(long)i);
        if (status != 0)
        {
            printf("Oops, pthread_create returned error code %d\n", status);
            exit(EXIT_FAILURE);
        }
    }

    //Generate Oompa loompa threads
    for (i = 0; i < NumOmpaLoopmpas; i++)
    {
        printf("[ MAIN ]      \t: Creating Oompa%d\n", i);
        status = pthread_create(&oompaLoompas[i], NULL, oompa_loompa_thread, (void *)(long)i);
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
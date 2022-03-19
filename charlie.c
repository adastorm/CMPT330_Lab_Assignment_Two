/*
Jonah Watts
2002006
CMPT330
*/


#include "ChocolateFactory.h"

// _  _ ____ ____ _ ____ ___  _    ____ ____ 
// |  | |__| |__/ | |__| |__] |    |___ [__  
//  \/  |  | |  \ | |  | |__] |___ |___ ___]
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
int isDoneProduction;

pthread_mutex_t lock;
pthread_cond_t condO, condC;

// ____ ____ _  _ _  _ ____ _   _ ____ ____ 
// |    |  | |\ | |  | |___  \_/  |  | |__/ 
// |___ |__| | \|  \/  |___   |   |__| |  \

void createConveyor(){
    //initialize the data and the array
    candiesInConveyor = 0;
    oompaPosition = 0;
    childPosition = 0;
    list = malloc(conveyorSize*sizeof(list));
}
int addToConveyor(struct candy input){
    //If the conveyor is full, return 0
    if (conveyorSize == candiesInConveyor)
        return 0;

    //if conveyor isnt full, add the object, and return 1
    else
    {
        candiesInConveyor++;
        list[oompaPosition] = input;
        oompaPosition++;
        if (oompaPosition >= conveyorSize)
            oompaPosition = 0;
        return 1;
    }
}

void printConveyor(){
    printf("________ Conveyor Size: %d\n",conveyorSize);
  
}



// _  _ ____ _ _  _ 
// |\/| |__| | |\ | 
// |  | |  | | | \|
//The main Thread
int main(int argc, const char *argv[])
{
    isDoneProduction = 1;
    // First check is there are enogh command line arguments
    if (argc != 6){
        printf("You Fail, Need Arguments\n");
        exit(EXIT_FAILURE);
    }

    // Take in the command line arguments
    NumOmpaLoopmpas = atoi(argv[1]);
    NumChildren     = atoi(argv[2]);
    conveyorSize    = atoi(argv[3]);
    candiesPerBox   = atoi(argv[4]);
    candiesPerOompa = atoi(argv[5]);

    // Create circular queue
    createConveyor();
    printf("Loompas: %d Children: %d  Conveyor: %d BoxSize: %d Candies per LOompa: %d\n", NumOmpaLoopmpas, NumChildren, conveyorSize, candiesPerBox, candiesPerOompa);
    
 
    // Create arrays for the threads
    pthread_cond_init(&condO, 0);
    pthread_cond_init(&condC, 0);
    pthread_t oompaLoompas[NumOmpaLoopmpas];
    pthread_t children[NumChildren];
    pthread_mutex_init(&lock, 0);
    

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



    //Join the threads
    for (i = 0; i < NumOmpaLoopmpas; i++)
        pthread_join(oompaLoompas[i],NULL);

    
    isDoneProduction = 0;
    pthread_cond_broadcast(&condC);
    
    for (i = 0; i < NumChildren; i++)
    {
        pthread_join(children[i], NULL);
    }


    //Destroy everything
    pthread_cond_destroy(&condC);
    pthread_cond_destroy(&condO);
    pthread_mutex_destroy(&lock);
    free(list);
    printConveyor();
    exit(EXIT_SUCCESS);
}
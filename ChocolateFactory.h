/*
Jonah Watts
2002006
CMPT330
*/

#ifndef HEADER_FILE
#define HEADER_FILE

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>


//The Initial Global Variables
extern int NumOmpaLoopmpas;
extern int NumChildren;
extern int conveyorSize;
extern int candiesPerOompa;
extern int candiesPerBox;
extern int candiesInConveyor;
extern int oompaPosition;
extern int childPosition;

//Create an array of all the different colors

static const char* colors[26][90] = {
{"Amazing Apple"}
,{"Bonkers Banana"}
,{"Crazy Caramel"}
,{"Delightful Doughnut"}
,{"Extravagant"}
,{"Fairlygood Fudge"}
,{"Great Grape"}
,{"Healing Honeydow"}
,{"Intreaguing"}
,{"Jumping Jelly-Beans"}
,{"Killer Kitkats"}
,{"Long Limes"}
,{"Massive Mango"}
,{"Normal Nuts"}
,{"Obsolete Orange"}
,{"Purple Pear"}
,{"Quaint Quart"}
,{"Red Raspberry"}
,{"Small Strawberry"}
,{"Tall Teal"}
,{"Underwhealming"}
,{"Verygood Veal"}
,{"Wierd Worms"}
,{"Xtreme Xzylaphone"}
,{"Yellow Yellow"}
,{"Zealed Zebra"}
};

//Structure for the Candy
struct candy{
    int flavor;
    int loop;
    int number;
};




//The Two Main Multithreaded Functions
void *oompa_loompa_thread(void *);
void *child_thread(void *);

//Global Functions
int addToConveyor(struct candy);

// Global Variables
extern int isDoneProduction;
extern struct candy *list;

//Create the mutex lock
extern pthread_mutex_t lock;
extern pthread_cond_t condO, condC;
#endif
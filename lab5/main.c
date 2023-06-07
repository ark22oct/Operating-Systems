/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: a19khan
 *
 * Created on February 17, 2022, 4:37 PM
 */

#include <stdio.h> /* printf */
#include <sys/types.h> /* pid_t */
#include <unistd.h> /* get_pid */
#include <stdlib.h>     /* exit, EXIT_FAILURE */
#include <sys/wait.h>  /* wait */
#include <pthread.h>
#include <sys/stat.h>

void * count(void *);
int globalNumber = 0;
int numOfThreads = 5;
//Create a mutex
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

int main(void) {
    int i=0;
    pthread_t counterThread[5];

    //Create the 5 threads
    while (i<numOfThreads){
       if (pthread_create(&counterThread[i], NULL, &count, NULL)){
           printf("An error was encountered during thread creation!");
       }
       i++;
    }
    //Wait for all treads to finish
    for (i=0; i<numOfThreads; i++){
        pthread_join(counterThread[i], NULL);
    }
    printf("Ending counter value: %d\n", globalNumber);

    return (0);
}

void * count(void * junk) {
    int loopCount = 0;
    
    pthread_mutex_lock(&mutex1);
    
    while (loopCount < 10) {
        int tmpNumber = globalNumber;
        printf("counter: %d, Thread: %ld, PID: %d\n",
                tmpNumber, pthread_self(), getpid());
        tmpNumber = globalNumber;
        tmpNumber++;
        usleep(random() % 2);
        globalNumber = tmpNumber;
        loopCount++;
    }
    pthread_mutex_unlock(&mutex1);
    
    return (0);
}



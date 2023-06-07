/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: a19khan
 *
 * Created on February 15, 2022, 3:56 PM
 */
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char input[100];
char firstCommand[100];
char secondCommand[100];

/*
 * 
 */
int main(int argc, char** argv) {
    
    printf("Input desired pipe command:");
    fgets(input, 100, stdin);
    
    int range;
    
    range = strlen(input) -1;
    
    int i=0;
    int j=0;
    int k=0;
    int indicator=0;
    
    while (i<range){
        
        if (input[i] == '|'){
            indicator = 1;
            i++;    
        }
        
        else if (indicator == 0 && input[i] != '|'){
            firstCommand[j] = input[i];
            j++;
    }
        else {
            secondCommand[k] = input[i];
            k++;
        }
        i++;
    }
    
    int fd[2];
    int pid;
    pipe(fd);
    pid = fork();
    
    
    if (pid != 0){
        dup2(fd[0],0);
        close(fd[1]);
        system(secondCommand);
    }
    
    else if (pid == 0) {
        dup2(fd[1],1);
        close(fd[0]);
        system(firstCommand);
        exit(0);
    }    
    

    return (EXIT_SUCCESS);
}


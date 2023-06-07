/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: a19khan
 *
 * Created on February 6, 2022, 7:08 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

/*
 * 
 */
int main(int argc, char** argv) {
    
    while (1) {
        printf("Your command >");
        char inputCommand [100];
        fgets(inputCommand,100,stdin);
        
        
        int final = strlen(inputCommand)-1;
        char finalCharacter = inputCommand[final -1];
        
        pid_t pid;
        int i;
        int j=0;
        
         
     for (i=0; i<1; i++){
         pid_t pid = fork();
         
         if (pid == 0){
             printf("CHILD with process ID: %d\n", pid);
             system(inputCommand);
             
        if (finalCharacter == '&'){
            printf("Parent not waiting for child to complete\n");
        }
        else{
            while (j < 1){
                waitpid(pid,NULL,0);
                j++;
            }
            printf("Parent waiting for child to complete\n");
         }
         exit(0);
         }
         
        else{
         waitpid(pid,NULL,0);
         printf("PARENT with process ID: %d\n", pid);
         continue;
        }
     }
    }

    return (EXIT_SUCCESS);
}


#include <stdlib.h>
#include <stdio.h>
#include "pri_queue.h"
/** @file pri_queue.c */
static Node_ptr_t head = NULL;
/**
 * Insert a Node into a priority queue.
 * @param priority
 * @param data
 * @author Abdulrehman Khan
 */
void PQ_insert(int priority, char * data) {
 //FIX THIS
    
    Node_ptr_t tmp;
    
    //Creating another pointer for new nodes being added
    Node_ptr_t newNode = malloc(sizeof(Node_t));
    newNode -> priority = priority;
    newNode -> data = data;
    
    //if it is the first number being inserted and nothing was in the linked list before it
    //or if the number being inserted holds higher priority then the head, it will become the head:
    if (head == NULL ||head -> priority < newNode -> priority ){
        newNode -> next=head;
        head = newNode;
    }
    //Linked list already contains a head or in other words is not empty and
    //If the number being inserted holds lower priority then the head:
    else{
        tmp= head;
        while(tmp-> next-> priority > newNode-> priority && tmp-> next != NULL){
            tmp=tmp-> next;      
        }
    //Placing the new priority in the adequate spot/place:
    newNode -> next = tmp -> next;
    tmp -> next= newNode;
    }
}
/**
 * Delete and return the node with the highest priority.
 * @return The highest priority Node.
 */
Node_ptr_t PQ_delete() {
  //FIX THIS
    
    //Creating a temporary node pointer
    Node_ptr_t tempNodePtr = (Node_ptr_t)malloc (sizeof(Node_ptr_t));
    
    //Making sure that the queue has a head (not null) and once checked, we will put the head
    //in our temporary node pointer and then returning foremost priority node
    while (head != NULL){
        tempNodePtr = head;
        head = head -> next;
        return tempNodePtr;
    }
    
}

/**
 * Do NOT modify this function.
 * @return A pointer to the head of the list.  (NULL if list is empty.)
 */
Node_ptr_t PQ_get_head() {
    return head;
}

/**
 * Do NOT modify this function.
 * @return the number of items in the queue
 */
int PQ_get_size() {
    int size = 0;
    Node_ptr_t tmp;
    for(tmp = head; tmp != NULL; tmp = tmp->next, size++)
        ;
    return size;
}

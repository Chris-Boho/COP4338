#include "mylist.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

/* all yours to code! */

int listlength();

struct node_t {
    char* str;
    struct node_t* prev;
    struct node_t* next;
};
typedef struct node_t node_t;

struct node_t* first = NULL;
struct node_t* currentptr = NULL;
struct node_t* last = NULL;

void insert(char* str)
{

     node_t* const temp = (struct node_t*) malloc(sizeof(node_t));
     temp->str = (char*) malloc( strlen(str) + 1);
     strcpy(temp->str, str);

     if (first == NULL) {
          last = temp;

          temp->next = first;
          first = temp;
     } else if (strcmp(first->str, temp->str) > 0){
          first->prev = temp;

          temp->next = first;
          first = temp;

     } else if (strcmp(first->str, temp->str) < 0){
          temp->next = first->next;
          temp->next->prev = temp;
          temp->prev = first;
          first->next = temp;
     }
}

void delete(char* str)
{
     int stop = 1;
     currentptr = first;

     while (currentptr != NULL && stop == 1) {

          if (strcmp(currentptr->str, str) == 0) {

               if (currentptr->prev == NULL) {
                    first = currentptr->next;
                    first->prev = NULL;
               } else {
                    currentptr->next->prev = currentptr->prev;
                    currentptr->prev->next = currentptr->next;
               }

               stop--;
          }

          currentptr = currentptr->next;
     }
}

void list(int reverse_order)
{

     int size = listlength();

     if (reverse_order == 0 && size != 0) {

          currentptr = first;
          int i = 0;

          while(currentptr != NULL) {
             printf("%d: %s \n", i, currentptr->str);
             currentptr = currentptr->next;
             i++;
          }
     }

     if (reverse_order == 1 && size != 0) {

          currentptr = last;
          int pos = listlength() - 1;

          while(currentptr != NULL) {
             printf("%d: %s \n", pos, currentptr->str);
             currentptr = currentptr->prev;
             pos--;
          }
     }

     if (size == 0) {
          printf("<empty>\n");
     }
}

int listlength(){
     int size = 0;
     struct node_t* tempptr = first;

     while(tempptr != NULL){
          size++;
          tempptr = tempptr -> next;
     }
     return size;
}

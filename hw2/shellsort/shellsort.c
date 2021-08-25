#include <stdio.h>

int rand(void);
int srand(unsigned int seed);
void shellsort(int v[], int n);

int next;
int SIZE;

int main(){
     srand(12345);
     SIZE = 10;
     int x[SIZE];

     //filling the array
     for (int i = 0; i < SIZE; i++) {
          x[i] = rand();
          printf("x[%d] = %d\n", i, x[i]);
     }

     shellsort(x, SIZE);

     return 0;
}

int rand(){
     next = next * 1103515245 + 12345;
     return (unsigned int)(next/65536) % 32768;
}

int srand(unsigned int seed){
     next = seed;
}

void shellsort(int v[], int n){
     int gap, i, j, temp;

     for (gap = n/2; gap > 0; gap /= 2) {
          for (i = gap; i < n; i++) {

               // 'v[j]<v[j+gap]' this is where its comparing two positions in the array
               for (j = i-gap; j >= 0 && v[j]<v[j+gap]; j-=gap) {
                    temp = v[j];
                    v[j] = v[j+gap];
                    v[j+gap] = temp;
               }
          }
     }

     //printing final sorted array
     for (int i = 0; i < SIZE; i++) {
          printf("v[%d] = %d\n", i, v[i]);
     }
}

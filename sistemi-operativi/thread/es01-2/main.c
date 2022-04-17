#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

struct thread_args {
    int* array;
    int len;
    int pari; // pari 0, dispari 1
};
typedef struct thread_args my_args;

void *somma(void* arguments){
    my_args* args = arguments;
    int sum = 0;
    for(int i = args->pari; i<args->len; i+=2){
        sum += args->array[i];
    }
    return sum;
}


int main(int argc, char const *argv[])
{
    pthread_t t1, t2;
    int a[9]= {1,2,3,4,5,6,7,8,9};
    int len = 9;
    my_args t1_args;
    my_args t2_args;
    t1_args.array = a;
    t1_args.len= len;
    t1_args.pari = 0;
    t2_args.array = a;
    t2_args.len= len;
    t2_args.pari = 1;
    
    pthread_create(&t1, NULL, &somma, (void *) &t1_args);
    pthread_create(&t2, NULL, &somma, (void *) &t2_args);

    int* ris1, *ris2;
    pthread_join(t1, (void*) &ris1);
    pthread_join(t2, (void*) &ris2);
    printf("Somma Pari: %d, Somma Dispari: %d", ris1, ris2);
    return 0;
}

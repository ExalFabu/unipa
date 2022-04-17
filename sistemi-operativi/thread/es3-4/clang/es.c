#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#define MAX 10

struct thread_args {
    int num_or_lett; // num 0, lett 1
};
typedef struct thread_args my_args;

void *gen_random(void* arguments){
    my_args* args = arguments;
    srand(time(NULL));
    int *r = malloc(sizeof(int) * MAX);
    // int r[MAX];
    for (int i = 0; i<MAX; i++){
        if(args->num_or_lett == 0){
            r[i] = random() % 10;
        }
        else{
            r[i] = random() % 26 + 97;
        }
    }
    return r;
}


int main(int argc, char const *argv[])
{
    pthread_t t1, t2;
    my_args t1_args;
    my_args t2_args;
    t1_args.num_or_lett = 0;
    t2_args.num_or_lett = 1;
    
    pthread_create(&t1, NULL, &gen_random, (void *) &t1_args);
    pthread_create(&t2, NULL, &gen_random, (void *) &t2_args);

    int* ris1, *ris2;
    pthread_join(t1, (void*) &ris1);
    pthread_join(t2, (void*) &ris2);

    for(int i = 0; i<MAX; i+=2){
        printf("%d%d%c%c",ris1[i], ris1[i+1], ris2[i], ris2[i+1]);
    }
    printf("\n");
    return 0;
}

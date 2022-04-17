#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#define DIM 3
struct thread_args {
    int matrice[DIM][DIM];
    int principale; // 1 se diagonali principali, 0 se secondarie
    int ris;
};

void* calcola_determinante(void* u_targs){
    struct thread_args* targs = (struct thread_args*) u_targs;
    int diag_offset = 0;
    if (targs->principale != 1) diag_offset = DIM-1;
    int somma = 0;
    for (size_t offset = 0; offset < DIM; offset++){
       int local_mult = 1;
       for (size_t i = 0; i < DIM; i++){
           int row = diag_offset == 0 ? i : diag_offset - i;
           int col = (i+offset) % DIM;
           local_mult *= targs->matrice[row][col];
       }
       somma += local_mult;
    }
    targs->ris = somma;

    return (void*) 1;
}
void matrixcopy(int src[DIM][DIM], int dst[DIM][DIM]){
    for (size_t i = 0; i < DIM; i++)
    {
        for (size_t j = 0; j < DIM; j++)
        {
            dst[i][j]=src[i][j];
        }
        
    }
    
}

void print_matrix(int m[DIM][DIM]){
    for (size_t i = 0; i < DIM; i++)
    {
        for (size_t j = 0; j < DIM; j++)
        {
            printf("%d\t", m[i][j]);
        }
        printf("\n"); 
    }

}

int main(int argc, char const *argv[])
{
    pthread_t tid1, tid2;
    int *ris1, *ris2;
    int matrice[DIM][DIM] = {
        {6,5,1},
        {4,1,2},
        {0,7,11}
    };
    struct thread_args t1, t2;
    matrixcopy(matrice, t1.matrice);
    t1.principale = 1;
    pthread_create(&tid1,NULL, &calcola_determinante, &t1);

    matrixcopy(matrice, t2.matrice);
    t2.principale = 0;
    pthread_create(&tid2,NULL, &calcola_determinante, &t2);

    pthread_join(tid1, (void**) &ris1);
    pthread_join(tid2, (void**) &ris2);

    int det = t1.ris - t2.ris;
    print_matrix(matrice);
    printf("\nDeterminante: %d\n", det);

    return 0;
}

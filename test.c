#include <stdio.h>
#include <string.h>
#include <mpi.h>

const int MAX_STRING = 100;

int main(){
    printf("hello world \n");
    char greeting[MAX_STRING];
    int comm_ez;
    int my_rank;

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_ez);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    if(my_rank != 0){
        sprintf(greeting, "Greeting from process %d of %d!", my_rank, comm_ez);
        MPI_Send(greeting, strlen(greeting)+1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
    } else {

        printf("Greeting from process %d of %d!\n", my_rank, comm_ez);
        for (int q = 1; q < comm_ez; q++){

            MPI_Recv(greeting, MAX_STRING, MPI_CHAR, q, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("%s\n", greeting);

        }
    }

    MPI_Finalize();


    return 0;
}
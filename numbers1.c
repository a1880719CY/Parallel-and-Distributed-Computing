#include <stdio.h>
#include <string.h>
#include <mpi.h>

int main(){
    int ProcessNum;
    int myRank;

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &ProcessNum);
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);

    int input[ProcessNum];
    int storeNum;
    int compareingNum;

    if (ProcessNum != 5 && myRank == 0){

        printf("this program should be run with 5 processes.\n");
        MPI_Abort(MPI_COMM_WORLD, 1);

    } else {

        printf("please enter numbers for the %d process: ", ProcessNum);
        fflush(stdout);
        for (int i = 0; i < 5; i++){

            scanf("%d", &input[i]);

        }

    }
    MPI_Scatter(input, 1, MPI_INT, &storeNum, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (myRank != ProcessNum - 1){

        MPI_Send(&storeNum, 1, MPI_INT, myRank + 1, 0, MPI_COMM_WORLD);

    }
    if (myRank != 0){

        MPI_Recv(&compareingNum, 1, MPI_INT, myRank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        if (compareingNum >= storeNum){

            printf("Process %d has at least one number out of order.\n", myRank);
        }
        printf("Process %d has now finished.\n", myRank);

    } else {

        printf("Process %d has now finished.\n", myRank);

    }

    

    MPI_Finalize();


    return 0;
}
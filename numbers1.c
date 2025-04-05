//YU Shun Chit
//a1880719
//description:
//This MPI program simulates a ring topology with 5 processes. Each process is assigned a number and compares it with the number from its left neighbour (rank - 1, modulo total processes).
//The goal is to detect if any process has a number that is out of order. A number is considered out of order if it is smaller than the number in its left neighbour process. Process 0 has no left neighbour and is automatically considered in order.
//Each process reports whether its number is out of order, and then indicates it has completed.

#include <stdio.h>
#include <string.h>
#include <mpi.h>

int main(){
    int ProcessNum; // Total number of processes
    int myRank;     // Rank of the current process (unique identifier)

    // Initialize MPI environment
    MPI_Init(NULL, NULL);
    // Get the total number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &ProcessNum);
    // Get the rank of the current process
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);

    int storeNum;               // Variable to store the number for each process
    int compareingNum;          // Variable to compare numbers between processes

        // Ensure the program runs with exactly 5 processes
    if (ProcessNum != 5 && myRank == 0){

        // If not running with 5 processes, terminate the program
        printf("this program should be run with 5 processes.\n");
        MPI_Abort(MPI_COMM_WORLD, 1);       // MPI_Abort is used to terminate the MPI program execution immediately.

    }

    // MPI program with hard-coded input for each process
    if (myRank == 0){

        // Process 0 assigns the number 5 to storeNum
        storeNum = 5;

    } else if (myRank == 1){

        // Process 1 assigns the number 7 to storeNum
        storeNum = 7;

    } else if (myRank == 2){

        // Process 2 assigns the number 9 to storeNum
        storeNum = 9;

    } else if (myRank == 3){

        // Process 3 assigns the number 1 to storeNum
        storeNum = 1;

    } else if (myRank == 4){

        // Process 4 assigns the number 13 to storeNum
        storeNum = 13;

    } 

    // Send the number to the next process in the ring (right neighbour)
    if (myRank != ProcessNum - 1){

        MPI_Send(&storeNum, 1, MPI_INT, myRank + 1, 0, MPI_COMM_WORLD);

    }
    // Compare the received number with the number of the left neighbour (process before it)
    if (myRank != 0){

        MPI_Recv(&compareingNum, 1, MPI_INT, myRank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        // Check if the current number is greater than or equal to the left neighbour
        if (compareingNum >= storeNum){

            printf("Process %d has at least one number out of order.\n", myRank);
        }
        printf("Process %d has now finished.\n", myRank);

    } else {

        // For process 0, no comparison is needed, just print that it finished
        printf("Process %d has now finished.\n", myRank);

    }

    
    // Finalize the MPI environment
    MPI_Finalize();


    return 0;
}
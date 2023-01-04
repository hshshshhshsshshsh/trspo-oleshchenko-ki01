#include <iostream>
#include <time.h>
#include <cstdlib>
#include <mpi.h>

int main(int argc, char** argv) {
    double* x = new double[PointN];
    double* y = new double[PointN];
    int ProcessRank, ProcessN;
    int PointN = 1000000, Count = 0;
    MPI_Status Status;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &ProcessN);
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcessRank;
    int* ReceivedPointN = new int[ProcessN];
    double* ReceivedPi = new double[ProcessN];
    double* ReceivedTime = new double[ProcessN];
    double* ReceivedStatus = new double[ProcessN];
      srand(time(NULL));

    if (ProcessRank == 0){
        for (int i = 0; i < PointN; i++){
            x[i] = (double)rand() / RAND_MAX;
            y[i] = (double)rand() / RAND_MAX;
        }
    }
    MPI_Bcast(x, N, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(y, N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    int k;
    if (ProcessN== 1) {
        k = PointN / ProcessN;
    }
    else {
        k = PointN / (ProcessN - 1);
    }
    int points_in_set = k * ProcessRank;

    if (ProcessRank == ProcessN - 1) points_in_set = N;

    if (ProcessRank != 0) {
        double start = MPI_Wtime();

        for (int i = 0; i < points_in_set; i++) {
            double z = sqrt(x[i] * x[i] + y[i] * y[i]);

            if (z <= 1){
                Count++;
            }
        }
        double pi = 4 * ((double)Count / (double)points_in_set);

        double end = MPI_Wtime();
        double seconds = (end - start);

        MPI_Send(&pi, 1, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD);
        MPI_Send(&seconds, 1, MPI_DOUBLE, 0, 2, MPI_COMM_WORLD);
        MPI_Send(&points_in_set, 1, MPI_INT, 0, 3, MPI_COMM_WORLD);
    }

    else if (ProcessRank == 0) {
        for (int i = 1; i < ProcessN; i++) {

            MPI_Recv(&ReceivedPi[i], 1, MPI_DOUBLE, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Recv(&ReceivedTime[i], 1, MPI_DOUBLE, MPI_ANY_SOURCE, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

MPI_Recv(&ReceivedPointN[i], 1, MPI_INT, MPI_ANY_SOURCE, 3, MPI_COMM_WORLD, &Status);

            ReceivedStatus[i] = Status.MPI_SOURCE;
        }
    }

    MPI_Barrier(MPI_COMM_WORLD);

    if (ProcessRank == 0) {
        for (int i = 1; i < ProcessN; i++) {

            std::cout << "`Process - status=" << ReceivedStatus[i] << " pi=" << ReceivedPi[i] << " time=" << ReceivedTime[i]

                << " points number=" << ReceivedPointN[i] << std::endl;
        }
    }

    MPI_Finalize();

    delete[] x;
    delete[] y;
    delete[] ReceivedPointN;
    delete[] ReceivedPi;
    delete[] ReceivedTime;
    delete[] ReceivedStatus;
    return 0;
}

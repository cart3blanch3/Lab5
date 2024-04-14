#include <mpi.h>
#include <iostream>

int main(int argc, char* argv[]) {
    int rank, size;
    int message; // ���������, ������� ����� ������������

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2) {
        std::cerr << "This program requires at least 2 processes to run." << std::endl;
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    if (rank == 0) { // ���� ��� ������� � ������� 0
        message = 45;
        MPI_Send(&message, 1, MPI_INT, 1, 0, MPI_COMM_WORLD); // ���������� ��������� �������� � ������� 1
    }
    else if (rank == 1) { // ���� ��� ������� � ������� 1
        MPI_Recv(&message, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); // ��������� ��������� �� �������� � ������� 0
        std::cout << "receive message '" << message << "'" << std::endl; // ������� �������� ���������
    }

    MPI_Finalize();

    return 0;
}

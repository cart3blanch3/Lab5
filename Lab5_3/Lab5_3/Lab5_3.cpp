#include <mpi.h>
#include <iostream>

int main(int argc, char* argv[]) {
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) { // ���� ��� ������� � ������� 0
        std::cout << size << " processes." << std::endl; // ������� ����� ���������� ���������

        // ������� 0 ���������� ��������� 1-��� ��������
       MPI_Send(NULL, 0, MPI_INT, 1, 0, MPI_COMM_WORLD);
    }
    else { // ��� ���� ��������� ���������
        MPI_Recv(NULL, 0, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); // ������� ��������� �� ����������� ��������

        if (rank % 2 != 0) { // ���� ����� �������� ��������
            std::cout << "I am " << rank << " process: FIRST!" << std::endl; // ������� FIRST
        }
        else {
            std::cout << "I am " << rank << " process: SECOND!" << std::endl; // ������� SECOND
        }

        if (rank != size - 1) { // ���� ��� �� ��������� �������
            MPI_Send(NULL, 0, MPI_INT, rank + 1, 0, MPI_COMM_WORLD); // �������� ���������� ���������� ��������
        }
    }

    MPI_Finalize();

    return 0;
}

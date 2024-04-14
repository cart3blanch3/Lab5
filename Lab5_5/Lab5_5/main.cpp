#include <mpi.h>
#include <iostream>

int main(int argc, char* argv[]) {
    int rank, size;
    int message;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2) {
        std::cerr << "This program requires at least 2 processes to run." << std::endl;
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    if (rank == 0) { // ���� ��� ������� � ������� 0
        message = rank; // �������������� ��������� ������� ��������
        MPI_Send(&message, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD); // ���������� ��������� ���������� ��������
    }
    else if (rank < size - 1) { // ���� ��� ������� � ������� �� 1 �� size-1 (�������� ���������)
        MPI_Recv(&message, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); // ��������� ��������� �� ����������� ��������
        std::cout << "[" << rank << "]: receive message '" << message << "'" << std::endl; // ������� �������� ���������
        ++message; // �������������� ���������
        MPI_Send(&message, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD); // ���������� ������������������ ��������� ���������� ��������
    }
    else { // ���� ��� ��������� �������
        MPI_Recv(&message, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); // ��������� ��������� �� ����������� ��������
        std::cout << "[" << rank << "]: receive message '" << message << "'" << std::endl; // ������� �������� ���������
    }

    MPI_Finalize();

    return 0;
}

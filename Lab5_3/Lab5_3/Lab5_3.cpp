#include <mpi.h>
#include <iostream>

int main(int argc, char* argv[]) {
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) { // Если это процесс с номером 0
        std::cout << size << " processes." << std::endl; // Выводим общее количество процессов

        // Процесс 0 отправляет сообщение 1-ому процессу
       MPI_Send(NULL, 0, MPI_INT, 1, 0, MPI_COMM_WORLD);
    }
    else { // Для всех остальных процессов
        MPI_Recv(NULL, 0, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); // Ожидаем сообщение от предыдущего процесса

        if (rank % 2 != 0) { // Если номер процесса нечетный
            std::cout << "I am " << rank << " process: FIRST!" << std::endl; // Выводим FIRST
        }
        else {
            std::cout << "I am " << rank << " process: SECOND!" << std::endl; // Выводим SECOND
        }

        if (rank != size - 1) { // Если это не последний процесс
            MPI_Send(NULL, 0, MPI_INT, rank + 1, 0, MPI_COMM_WORLD); // Передаем управление следующему процессу
        }
    }

    MPI_Finalize();

    return 0;
}

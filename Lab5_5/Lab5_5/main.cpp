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

    if (rank == 0) { // Если это процесс с номером 0
        message = rank; // Инициализируем сообщение номером процесса
        MPI_Send(&message, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD); // Отправляем сообщение следующему процессу
    }
    else if (rank < size - 1) { // Если это процесс с номером от 1 до size-1 (исключая последний)
        MPI_Recv(&message, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); // Принимаем сообщение от предыдущего процесса
        std::cout << "[" << rank << "]: receive message '" << message << "'" << std::endl; // Выводим принятое сообщение
        ++message; // Инкрементируем сообщение
        MPI_Send(&message, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD); // Отправляем инкрементированное сообщение следующему процессу
    }
    else { // Если это последний процесс
        MPI_Recv(&message, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); // Принимаем сообщение от предыдущего процесса
        std::cout << "[" << rank << "]: receive message '" << message << "'" << std::endl; // Выводим принятое сообщение
    }

    MPI_Finalize();

    return 0;
}

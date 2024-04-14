#include <mpi.h> 
#include <iostream>

int main(int argc, char* argv[]) {
    int rank, size; // Переменные для хранения номера процесса и общего количества процессов

    MPI_Init(&argc, &argv); // Инициализируем MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Получаем номер текущего процесса
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Получаем общее количество процессов

    // Выводим сообщение с номером процесса и общим количеством процессов
    std::cout << "I am " << rank << " process from " << size << " processes!" << std::endl;

    MPI_Finalize(); // Завершаем работу MPI

    return 0;
}

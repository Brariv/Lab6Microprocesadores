#include <iostream>
#include <pthread.h>
#include <vector>

const int N = 4;  // Tamaño de las matrices (N x N)
int A[N][N], B[N][N], C[N][N];  // Matrices de entrada y salida

struct ThreadData {
    int startRow;
    int endRow;
};

void* sumMatrices(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    int startRow = data->startRow;
    int endRow = data->endRow;

    for (int i = startRow; i < endRow; ++i) {
        for (int j = 0; j < N; ++j) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }

    pthread_exit(NULL);
}

int main() {
    // Solicitar entrada del usuario para la matriz A
    std::cout << "Ingrese los valores de la matriz A (" << N << "x" << N << "):\n";
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            std::cin >> A[i][j];
        }
    }

    // Solicitar entrada del usuario para la matriz B
    std::cout << "Ingrese los valores de la matriz B (" << N << "x" << N << "):\n";
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            std::cin >> B[i][j];
        }
    }

    int numThreads = 2;  // Número de hilos
    pthread_t threads[numThreads];
    ThreadData threadData[numThreads];

    int rowsPerThread = N / numThreads;

    // Crear hilos y asignar filas a cada uno
    for (int i = 0; i < numThreads; ++i) {
        threadData[i].startRow = i * rowsPerThread;
        threadData[i].endRow = (i + 1) * rowsPerThread;

        pthread_create(&threads[i], NULL, sumMatrices, (void*)&threadData[i]);
    }

    // Esperar a que los hilos terminen
    for (int i = 0; i < numThreads; ++i) {
        pthread_join(threads[i], NULL);
    }

    // Imprimir la matriz resultante C
    std::cout << "Resultado de la suma de matrices:\n";
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            std::cout << C[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}

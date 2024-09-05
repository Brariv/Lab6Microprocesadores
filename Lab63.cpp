#include <iostream>
#include <pthread.h>
#include <vector>

struct ThreadData {
    int* row;
    int count;
    int rowLength;
};

int** matrixgenerator(int n){
    int** matrix = new int*[n];
    for (int i = 0; i < n; i++){
        matrix[i] = new int[n];
        for (int j = 0; j < n; j++){
            matrix[i][j] = rand() % 2;
        }
    }
    return matrix;
}

void printMatrix(int** matrix, int n){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void* countLiveCells(void* arg);

int livecells(int** matrix, int n) {
    const int numThreads = n;
    pthread_t threads[numThreads];
    ThreadData threadData[numThreads];

    int count = 0;
    for (int i = 0; i < n; i++) {
        threadData[i].row = matrix[i];
        threadData[i].count = 0;
        threadData[i].rowLength = n;
    }

    for (int i = 0; i < numThreads; i++) {
        pthread_create(&threads[i], NULL, &countLiveCells, &threadData[i]);
    }

    for (int i = 0; i < numThreads; i++) {
        pthread_join(threads[i], NULL);
        count += threadData[i].count;
    }

    return count;
}

void* countLiveCells(void* arg) {
    ThreadData* threadData = static_cast<ThreadData*>(arg);
    int* row = threadData->row;
    int rowLength = threadData->rowLength;
    int count = 0;
    for (int i = 0; i < rowLength; i++) {
        if (row[i] == 1) {
            count++;
        }
    }
    threadData->count = count;
    return NULL;
}

int main(){
    std::cout << "Enter the size of the matrix: ";
    int n;
    std::cin >> n;
    int** matrix = matrixgenerator(n);
    printMatrix(matrix, n);
    int count = livecells(matrix, n);
    std::cout << "Number of live cells: " << count << std::endl;
    return 0;
}



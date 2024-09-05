#include <iostream>
#include <pthread.h>
#include <fstream> 
#include <vector> 
#include <sstream>

// Define a structure to hold the data and the result
struct ThreadData {
    std::vector<std::string>* data;
    int count;
};

// Thread function to count words
void* countWords(void* arg) {
    ThreadData* threadData = static_cast<ThreadData*>(arg);
    std::vector<std::string>* data = threadData->data;
    int count = 0;
    for (const auto& line : *data) {
        std::istringstream stream(line);
        std::string word;
        while (stream >> word) {
            count++;
        }
    }
    threadData->count = count;
    return nullptr;
}

std::vector<std::string> readTxtFile(std::string filename) {
    // Open the file
    std::vector<std::string> words; // Add 'std::' before 'vector'
    std::string word;
    std::string line;
    std::ifstream file(filename);
    //add file to string
    while (getline(file, line)) {
        words.push_back(line); 
    }

    return words;
}

int Threads(std::vector<std::string> Data) {
    int countf = 0;
    const int numThreads = 4;
    pthread_t threads[numThreads];
    ThreadData threadData[numThreads];


    std::vector<std::string> threads1;
    std::vector<std::string> threads2;
    std::vector<std::string> threads3;
    std::vector<std::string> threads4;

    for (int i = 0; i < Data.size(); i++) {
        if (i == 0 || i == 1) {
            threads1.push_back(Data[i]);
        } else if (i == 2 || i == 3) {
            threads2.push_back(Data[i]);
        } else if (i == 4 || i == 5) {
            threads3.push_back(Data[i]);
        } else {
            threads4.push_back(Data[i]);
        }
    }
    threadData[0].data = &threads1;
    threadData[1].data = &threads2;
    threadData[2].data = &threads3;
    threadData[3].data = &threads4;

    threadData[0].count = 0;
    threadData[1].count = 0;
    threadData[2].count = 0;
    threadData[3].count = 0;

    
    
    for (int i = 0; i < numThreads; i++) {
        pthread_create(&threads[i], NULL, &countWords, &threadData[i]);
        
    }
    for (int i = 0; i < numThreads; ++i){
        pthread_join(threads[i], NULL); 
        countf += threadData[i].count;  
    }

    return countf;
    
    
}


int main() {
    std::vector<std::string> readTxtFile(std::string filename);
    std::string filename = "words.txt";
    std::vector<std::string> Data = readTxtFile(filename);
    int count = Threads(Data);
    std::cout << "Number of words: " << count << std::endl;
    
}
    
    




#include <iostream>
#include <fstream>
#include <pthread.h>
#include <vector>
#include <string>
#include <mutex>
#include <sstream>  

std::mutex mtx;
int total_word_count = 0;

void* countWords(void* arg) {
    std::string section = *(std::string*)arg;
    int word_count = 0;

    std::istringstream stream(section);
    std::string word;
    while (stream >> word) {
        word_count++;
    }

    std::lock_guard<std::mutex> lock(mtx);
    total_word_count += word_count;

    pthread_exit(NULL);
}

int main() {
    std::ifstream file("texto.txt");
    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo." << std::endl;
        return 1;
    }

    file.seekg(0, std::ios::end);
    size_t file_size = file.tellg();
    size_t section_size = file_size / 4;  

    std::vector<std::string> sections(4);
    file.seekg(0, std::ios::beg);

    for (int i = 0; i < 4; i++) {
        std::vector<char> buffer(section_size);
        file.read(buffer.data(), section_size);
        sections[i] = std::string(buffer.begin(), buffer.end());
    }

    pthread_t threads[4];

    for (int i = 0; i < 4; i++) {
        pthread_create(&threads[i], NULL, countWords, (void*)&sections[i]);
    }

    for (int i = 0; i < 4; i++) {
        pthread_join(threads[i], NULL);
    }

    file.close();

    std::cout << "Número total de palabras: " << total_word_count << std::endl;

    return 0;
}

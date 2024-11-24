#include <iostream>
#include <vector>
#include <cstdlib>
#include <omp.h>
#include <fstream>

const int count = 10000000;
int max = -1;
double avg_sum = 0.0;

void fill_array(std::vector<int>& array) {
    for (int i = 0; i < count; i++) {
        array[i] = rand();
    }
}

double sort_array(std::vector<int>& array, int threads) {
    double start_time = omp_get_wtime();
    #pragma omp parallel num_threads(threads) shared(array, count) reduction(max: max) default(none) 
    {
        #pragma omp for
        for (int i = 0; i < count; i++) {
            if (array[i] > max) {
                max = array[i];
            }
        }   
    }
    double end_time = omp_get_wtime();
    return (end_time - start_time);
}

void control_method(int threads, int random_seed, std::ofstream& results_file) {
    srand(random_seed);
    std::vector<int> array(count);
    fill_array(array);
    double result = sort_array(array, threads);
    
    // Запись промежуточного результата в файл
    results_file << "Threads: " << threads << ", Random Seed: " << random_seed << ", Time: " << result << " seconds" << std::endl;
    
    avg_sum += result;
}

int main() {
    // Открытие файла для записи результатов
    std::ofstream results_file("results.txt", std::ios::out);
    if (!results_file.is_open()) {
        std::cerr << "Failed to open results file!" << std::endl;
        return 1;
    }

    double start_program_time = omp_get_wtime();  // Запись времени начала работы программы

    std::cout << "Max threads: " << omp_get_max_threads() << std::endl;

    for (int i = 1; i <= 4; i++) {
        int random_seed = 920215;
        for (int j = 0; j < 50; j++) {
            control_method(i, random_seed + j, results_file);    
        }
        avg_sum /= 50.0;
        
        std::cout << "--------------------------------" << std::endl;
        std::cout << "AVERAGE_SUM: " << avg_sum << std::endl;
        results_file << "AVERAGE_SUM for " << i << " threads: " << avg_sum << std::endl;
        avg_sum = 0.0;
    }

    double end_program_time = omp_get_wtime();  // Запись времени окончания работы программы
    double total_program_time = end_program_time - start_program_time;

    std::cout << "Total program execution time: " << total_program_time << " seconds" << std::endl;
    results_file << "Total program execution time: " << total_program_time << " seconds" << std::endl;

    // Закрытие файла
    results_file.close();

    return 0;
}

#include "Memeplexes_Shuffling.h"
#include "GlobaLData.h"

void Memeplexes_Shuffling::shuffle_memeplexes() {
    while (true) {
        wait(global_data.memeplexes_optimized_event);

        std::vector<int> updated_fitness = global_data.fitness;

        int frogs_per_memeplex = global_data.frogs_num / global_data.memeplexes_num;
        int index = 0;
        for (int m = 0; m < global_data.memeplexes_num; ++m) {
            for (int f = 0; f < frogs_per_memeplex; ++f) {
                global_data.population[index] = global_data.memeplexes[m][f];
                global_data.fitness[index] = updated_fitness[global_data.memeplexes_num * f + m];
                index++;
            }
        }

        cout << "--------------------------------------------------------------" << endl;
        cout << "Population after shuffling memeplexes :" << endl;
        index = 0;
        for (int i = 0; i < global_data.frogs_num; i++) {
            cout << "Frog " << i + 1 << ": ";
            for (int j = 0; j < global_data.items_num; j++) {
                cout << global_data.population[i][j];
            }
            std::cout << " | Fitness: " << global_data.fitness[index] << "\n";
            index++;
        }
        global_data.fitness_evaluated_event.notify(SC_ZERO_TIME);
    }

}
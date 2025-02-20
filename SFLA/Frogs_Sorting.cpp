#include "Frogs_Sorting.h"
#include "GlobalData.h"
#include <algorithm>

void Frogs_Sorting::sort_population() {
    while (true) {
        wait(global_data.fitness_evaluated_event);

        for (int i = 0; i < global_data.frogs_num; ++i) {
            for (int j = i + 1; j < global_data.frogs_num; ++j) {
                if (global_data.fitness[i] < global_data.fitness[j]) {
                    std::swap(global_data.fitness[i], global_data.fitness[j]);
                    std::swap(global_data.population[i], global_data.population[j]);
                }
            }
        }

        cout << "--------------------------------------------------------------" << endl;
        cout << "Sorted Frogs Population (by Fitness):" << endl;
        for (int i = 0; i < global_data.frogs_num; i++) {
            cout << "Frog " << i + 1 << ": ";
            for (int j = 0; j < global_data.items_num; j++) {
                cout << global_data.population[i][j];
            }
            cout << " | Fitness: " << global_data.fitness[i] << endl;
        }
        global_data.sorting_done_event.notify(SC_ZERO_TIME);
    }
}
#include "Performance_Evaluation.h"
#include "GlobalData.h"
#include <iostream>

void Performance_Evaluation::evaluate_fitness() {
    wait(global_data.population_generated_event);

    for (int i = 0; i < global_data.frogs_num; i++) {
        int total_price = 0, total_weight = 0;
        for (int j = 0; j < global_data.items_num; j++) {
            if (global_data.population[i][j]) {
                total_price += global_data.items[j].price;
                total_weight += global_data.items[j].weight;
            }
        }
        global_data.fitness[i] = (total_weight > global_data.max_weight) ? 0 : total_price;
    }

    cout << "--------------------------------------------------------------" << endl;
    cout << "Initial Random Frogs Population:" << endl;
    for (int i = 0; i < global_data.frogs_num; i++) {
        cout << "Frog " << i + 1 << ": ";
        for (int j = 0; j < global_data.items_num; j++) {
            cout << global_data.population[i][j];
        }
        cout << " | Fitness: " << global_data.fitness[i] << endl;
    }
    global_data.fitness_evaluated_event.notify(SC_ZERO_TIME);

}
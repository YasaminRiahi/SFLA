#include "Frog_Population.h"
#include "GlobalData.h"
#include <cstdlib>
#include <iostream>
#include <random>

void Frog_Population::generate_population() {
    wait(global_data.parameters_set_event);
    std::random_device rd;
    std::mt19937 gen(rd());
    for (int i = 0; i < global_data.frogs_num; i++) {
        for (int j = 0; j < global_data.items_num; j++) {
            global_data.population[i][j] = std::uniform_int_distribution<>(0, 1)(gen);
        }
    }
    global_data.population_generated_event.notify(SC_ZERO_TIME);
    wait(SC_ZERO_TIME);
}

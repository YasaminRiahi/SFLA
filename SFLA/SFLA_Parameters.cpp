#include "SFLA_Parameters.h"
#include "GlobalData.h"

void SFLA_Parameters::set_parameters() {
    global_data.frogs_num = 20;
    global_data.items_num = 9;
    global_data.memeplexes_num = 5;
    global_data.q_frogs = 3;
    global_data.max_local_iterations_num = 5;
    global_data.max_global_iterations_num = 50;
    global_data.max_weight = 25;
    global_data.fitness.resize(global_data.frogs_num, 0);
    global_data.population.resize(global_data.frogs_num, std::vector<bool>(global_data.items_num, false));
    global_data.convergence_count = 0;
    global_data.last_best_fitness = 0;
    global_data.global_iterations = 0;

    cout << "Frogs: " << global_data.frogs_num << endl;
    cout << "Memeplexes: " << global_data.items_num << endl;
    cout << "Max Local Iterations: " << global_data.max_local_iterations_num << endl;
    cout << "Items: " << global_data.items_num << endl;
    cout << "Q Frogs: " << global_data.q_frogs << endl;

    global_data.parameters_set_event.notify(SC_ZERO_TIME);
}
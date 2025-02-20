#ifndef GLOBAL_DATA_H
#define GLOBAL_DATA_H
#include <systemc.h>
#include <vector>

struct Item {
    int price;
    int weight;
};

class GlobalData {
public:
    int frogs_num;
    int memeplexes_num;
    int max_local_iterations_num;
    int max_global_iterations_num;
    int global_iterations;
    int items_num;
    int q_frogs;
    double s_max = 1.0;
    bool convergence;
    std::vector<std::vector<bool>> population;
    std::vector<int> fitness;
    std::vector<std::vector<std::vector<bool>>> memeplexes;
    int convergence_count;
    int last_best_fitness;
    int max_weight;

    Item items[9] = {
        {6, 2}, {5, 3}, {8, 6}, {9, 7}, {6, 5},
        {7, 9}, {3, 3}, {6, 4}, {8, 5}
    };

    sc_event parameters_set_event;
    sc_event population_generated_event;
    sc_event fitness_evaluated_event;
    sc_event sorting_done_event;
    sc_event memeplexes_partitioned_event;
    sc_event memeplexes_optimized_event;
    sc_event convergence_checked_event;
    sc_event monitor_event;
    sc_event monitoring_done_event;

};

extern GlobalData global_data;

#endif 

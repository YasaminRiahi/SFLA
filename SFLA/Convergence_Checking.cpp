#include "Convergence_Checking.h"
#include "GlobaLData.h"

void Convergence_Checking::check_convergence() {
    while (true) {
        wait(global_data.sorting_done_event);
        if (global_data.fitness[0] == global_data.last_best_fitness) {
            global_data.convergence_count++;
        }
        else {
            global_data.convergence_count = 0;
        }

        global_data.last_best_fitness = global_data.fitness[0];

        global_data.monitor_event.notify(SC_ZERO_TIME);

        wait(global_data.monitoring_done_event);

        if (global_data.convergence_count >= 10 || global_data.global_iterations > 100) {
            sc_stop();
        }

        global_data.global_iterations++;
        global_data.convergence_checked_event.notify(SC_ZERO_TIME);

    }
}
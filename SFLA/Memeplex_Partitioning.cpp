#include "Memeplex_Partitioning.h"
#include "GlobalData.h"

void Memeplex_Partitioning::partition_population() {
    while (true) {
        wait(global_data.convergence_checked_event);

        int frogs_per_memeplex = global_data.frogs_num / global_data.memeplexes_num;
        global_data.memeplexes.assign(global_data.memeplexes_num, std::vector<std::vector<bool>>(frogs_per_memeplex));

        for (int m = 0; m < global_data.memeplexes_num; ++m) {
            for (int f = 0; f < frogs_per_memeplex; ++f) {
                global_data.memeplexes[m][f] = global_data.population[global_data.memeplexes_num * f + m];
            }
        }
        std::cout << "Memeplexes after Partitioning:" << std::endl;
        for (size_t m = 0; m < global_data.memeplexes.size(); ++m) {
            std::cout << "Memeplex " << m + 1 << ":\n";
            for (size_t f = 0; f < global_data.memeplexes[m].size(); ++f) {
                for (bool gene : global_data.memeplexes[m][f]) {
                    std::cout << gene;
                }
                std::cout << " | Fitness: " << global_data.fitness[global_data.memeplexes_num * f + m] << "\n";
            }
        }

        global_data.memeplexes_partitioned_event.notify(SC_ZERO_TIME);
    }
}
#include <systemc.h>
#include "GlobaLData.h"

SC_MODULE(Monitor) {
    void monitoring() {
        while (true) {
            wait(global_data.monitor_event);
            cout << "==================================================================================="
                << "\n" << "Iteration : " << global_data.global_iterations;
            cout << "         Best Fitness : " << global_data.fitness[0] << "       Best Choise : ";
            for (int i = 0; i < global_data.items_num; i++)
            {
                cout << global_data.population[0][i] << " ";
            }
            cout << "\n" << "===================================================================================" << "\n";
            global_data.monitoring_done_event.notify(SC_ZERO_TIME);
        }
    }

    SC_CTOR(Monitor) {
        SC_THREAD(monitoring);
    }
};

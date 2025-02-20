#include "SFLA_Parameters.h"
#include "Frog_Population.h"
#include "Performance_Evaluation.h"
#include "Frogs_Sorting.h"
#include "Convergence_Checking.h"
#include "Memeplex_Partitioning.h"
#include "Local_Search.h"
#include "Memeplexes_Shuffling.h"
#include <iostream>
#include <systemc.h>
#include "GlobalData.h" 
#include "Monitor.h"

GlobalData global_data;

int sc_main(int argc, char* argv[]) {
    SFLA_Parameters parameters("Parameters");
    Frog_Population frog_population("Frog_Population");
    Performance_Evaluation performance_evaluation("Performance_Evaluation");
    Frogs_Sorting frogs_sorting("Frogs_Sorting");
    Convergence_Checking convergence_checking("Convergence_Checking");
    Monitor monitor("Monitor");
    Memeplex_Partitioning memeplex_partitioning("Memeplex_Partitioning");
    Local_Search local_search("Local_Search");
    Memeplexes_Shuffling memeplexes_shuffling("Memeplexes_Shuffling");


    sc_start(100, SC_SEC);

    return 0;
}


#include <systemc.h>

SC_MODULE(Performance_Evaluation) {
    void evaluate_fitness();
    SC_CTOR(Performance_Evaluation) {
        SC_THREAD(evaluate_fitness);
    }
};
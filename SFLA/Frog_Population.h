#include <systemc.h>

SC_MODULE(Frog_Population) {
    void generate_population();
    SC_CTOR(Frog_Population) {
        SC_THREAD(generate_population);
    }
};

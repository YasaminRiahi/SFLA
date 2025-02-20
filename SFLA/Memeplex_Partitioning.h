#include <systemc.h>

SC_MODULE(Memeplex_Partitioning) {
    void partition_population();
    SC_CTOR(Memeplex_Partitioning) {
        SC_THREAD(partition_population);
    }
};
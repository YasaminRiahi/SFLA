#include <systemc.h>

SC_MODULE(Frogs_Sorting) {
    void sort_population();
    SC_CTOR(Frogs_Sorting) {
        SC_THREAD(sort_population);
    }
};
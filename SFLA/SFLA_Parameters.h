#include <systemc.h>

SC_MODULE(SFLA_Parameters) {
    void set_parameters();
    SC_CTOR(SFLA_Parameters) {
        SC_THREAD(set_parameters);
    }
};
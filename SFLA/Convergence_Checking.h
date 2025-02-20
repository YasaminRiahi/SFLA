#pragma once
#include <systemc.h>
#include <vector>

SC_MODULE(Convergence_Checking) {
    void check_convergence();

    SC_CTOR(Convergence_Checking) {
        SC_THREAD(check_convergence);
    }
};
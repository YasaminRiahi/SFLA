#include <systemc.h>
#include <vector>
#include <algorithm>

SC_MODULE(Memeplexes_Shuffling) {
    void shuffle_memeplexes();

    SC_CTOR(Memeplexes_Shuffling) {
        SC_THREAD(shuffle_memeplexes);
    }
};
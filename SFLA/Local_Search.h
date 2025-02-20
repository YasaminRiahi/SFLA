#include <systemc.h>

SC_MODULE(Local_Search) {
    void local_search(int memeplex_id);
    int which_thread = 0;

    SC_CTOR(Local_Search) {
        SC_THREAD(local_search_1);
        SC_THREAD(local_search_2);
        SC_THREAD(local_search_3);
        SC_THREAD(local_search_4);
        SC_THREAD(local_search_5);
    }

    void local_search_1() { local_search(0); }
    void local_search_2() { local_search(1); }
    void local_search_3() { local_search(2); }
    void local_search_4() { local_search(3); }
    void local_search_5() { local_search(4); }
};

void apply_Local_optimization(std::vector<std::vector<bool>>& memeplex, int best_frog, int worst_frog);
void apply_global_optimization(std::vector<std::vector<bool>>& memeplex, const std::vector<bool>& global_best_frog, int worst_frog);
int evaluate_fitness(const std::vector<bool>& frog);
std::vector<int> select_q_frogs(int n, int q);
int find_best_frog_in_memeplex(const std::vector<std::vector<bool>>& memeplex, const std::vector<int>& selected_frogs_indexes);
int find_worst_frog_in_memeplex(const std::vector<std::vector<bool>>& memeplex, const std::vector<int>& selected_frogs_indexes);
std::vector<bool> find_global_best_frog(const std::vector<std::vector<std::vector<bool>>>& memeplexes);
std::vector<bool> generate_random_frog(size_t size);

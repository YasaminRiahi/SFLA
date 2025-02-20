#include "Local_Search.h"
#include "GlobalData.h"
#include <random>


void Local_Search::local_search(int memeplex_id) {
    while (true) {
        wait(global_data.memeplexes_partitioned_event);
        which_thread++;
        int frogs_per_memeplex = global_data.frogs_num / global_data.memeplexes_num;
        std::vector<int> selected_frogs_indexes = select_q_frogs(frogs_per_memeplex, global_data.q_frogs);
        std::vector<std::vector<bool>> updated_memeplex = global_data.memeplexes[memeplex_id];
        cout << "--------------------------------------------------------------" << endl;
        cout << "Selected Frogs: ";
        for (int i = 0; i < selected_frogs_indexes.size(); i++)
        {
            cout << selected_frogs_indexes[i] << "  ";
        }
        cout << "\n";

        for (int iter = 0; iter < global_data.max_local_iterations_num; ++iter) {
            int best_frog = find_best_frog_in_memeplex(updated_memeplex, selected_frogs_indexes);
            int worst_frog = find_worst_frog_in_memeplex(updated_memeplex, selected_frogs_indexes);;
            apply_Local_optimization(updated_memeplex, best_frog, worst_frog);

            if (evaluate_fitness(updated_memeplex[worst_frog]) <= evaluate_fitness(global_data.memeplexes[memeplex_id][worst_frog])) {
                std::vector<bool> global_best_frog = find_global_best_frog(global_data.memeplexes);
                apply_global_optimization(updated_memeplex, global_best_frog, worst_frog);

                if (evaluate_fitness(updated_memeplex[worst_frog]) <= evaluate_fitness(global_data.memeplexes[memeplex_id][worst_frog])) {
                    updated_memeplex[worst_frog] = generate_random_frog(global_data.items_num);
                }

            }


            global_data.fitness[global_data.memeplexes_num * worst_frog + memeplex_id] = evaluate_fitness(updated_memeplex[worst_frog]);
            global_data.memeplexes[memeplex_id] = std::vector<std::vector<bool>>(updated_memeplex);

            std::cout << "Itration " << iter + 1 << "  Memeplex " << memeplex_id + 1 << ":\n";
            for (size_t f = 0; f < global_data.memeplexes[memeplex_id].size(); ++f) {
                for (bool gene : global_data.memeplexes[memeplex_id][f]) {
                    std::cout << gene;
                }
                std::cout << " | Fitness: " << evaluate_fitness(global_data.memeplexes[memeplex_id][f]) << "\n";
            }
        }
        if (which_thread == 5) {
            cout << "--------------------------------------------------------------" << endl;
            std::cout << "Final Optimized Memeplexes:" << std::endl;
            for (size_t m = 0; m < global_data.memeplexes.size(); ++m) {
                std::cout << "Memeplex " << m + 1 << ":\n";
                for (size_t f = 0; f < global_data.memeplexes[m].size(); ++f) {
                    for (bool gene : global_data.memeplexes[m][f]) {
                        std::cout << gene;
                    }
                    std::cout << " | Fitness: " << evaluate_fitness(global_data.memeplexes[m][f]) << "\n";
                }
            }
            which_thread = 0;
            global_data.memeplexes_optimized_event.notify(SC_ZERO_TIME);
        }
    }

}

void apply_Local_optimization(std::vector<std::vector<bool>>& memeplex, int best_frog, int worst_frog) {
    std::random_device rd;
    std::mt19937 gen(rd());
    double r = static_cast<double>(std::uniform_int_distribution<>(0, RAND_MAX)(gen)) / RAND_MAX;
    for (size_t k = 0; k < memeplex[0].size(); ++k) {
        double S = r * (memeplex[best_frog][k] - memeplex[worst_frog][k]);
        S = std::min(S, global_data.s_max);
        S = std::max(S, -global_data.s_max);
        if (S > 0.5)
        {
            memeplex[worst_frog][k] = memeplex[worst_frog][k] ^ 1;
        }
        else
        {
            memeplex[worst_frog][k] = memeplex[worst_frog][k] ^ 0;
        }
    }
}

void apply_global_optimization(std::vector<std::vector<bool>>& memeplex, const std::vector<bool>& global_best_frog, int worst_frog) {
    double r = static_cast<double>(rand()) / RAND_MAX;
    for (size_t k = 0; k < memeplex[0].size(); ++k) {
        double S = r * (global_best_frog[k] - memeplex[worst_frog][k]);
        S = std::min(S, global_data.s_max);
        S = std::max(S, -global_data.s_max);
        if (S > 0.5)
        {
            memeplex[worst_frog][k] = memeplex[worst_frog][k] ^ 1;
        }
        else
        {
            memeplex[worst_frog][k] = memeplex[worst_frog][k] ^ 0;
        }
    }
}

int evaluate_fitness(const std::vector<bool>& frog) {
    int total_price = 0;
    int total_weight = 0;

    for (size_t i = 0; i < frog.size(); ++i) {
        if (frog[i]) {
            total_price += global_data.items[i].price;
            total_weight += global_data.items[i].weight;
        }
    }

    return (total_weight > global_data.max_weight) ? 0 : total_price;
}


std::vector<int> select_q_frogs(int n, int q) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::vector<int> frog_pool;
    for (int j = 1; j <= n; ++j) {
        for (int k = 0; k < (n + 1 - j); ++k) {
            frog_pool.push_back(j - 1);
        }
    }

    std::vector<int> selected_frogs;
    for (int i = 0; i < q; ++i) {
        int random_index = std::uniform_int_distribution<>(0, frog_pool.size() - 1)(gen);
        int selected_frog = frog_pool[random_index];
        selected_frogs.push_back(selected_frog);
        frog_pool.erase(std::remove(frog_pool.begin(), frog_pool.end(), selected_frog), frog_pool.end());
    }

    return selected_frogs;
}

int find_best_frog_in_memeplex(const std::vector<std::vector<bool>>& memeplex, const std::vector<int>& selected_frogs_indexes) {
    int best_frog = selected_frogs_indexes[0];
    int best_fitness = evaluate_fitness(memeplex[best_frog]);

    for (int frog : selected_frogs_indexes) {
        int fitness = evaluate_fitness(memeplex[frog]);
        if (fitness > best_fitness) {
            best_frog = frog;
            best_fitness = fitness;
        }
    }

    return best_frog;
}

int find_worst_frog_in_memeplex(const std::vector<std::vector<bool>>& memeplex, const std::vector<int>& selected_frogs_indexes) {
    int worst_frog = selected_frogs_indexes[0];
    int worst_fitness = evaluate_fitness(memeplex[worst_frog]);

    for (int frog : selected_frogs_indexes) {
        int fitness = evaluate_fitness(memeplex[frog]);
        if (fitness < worst_fitness) {
            worst_frog = frog;
            worst_fitness = fitness;
        }
    }

    return worst_frog;
}

std::vector<bool> find_global_best_frog(const std::vector<std::vector<std::vector<bool>>>& memeplexes) {
    std::vector<bool> best_frog;
    int best_fitness = 0;

    for (const auto& memeplex : memeplexes) {
        for (const auto& frog : memeplex) {
            int fitness = evaluate_fitness(frog);
            if (fitness > best_fitness) {
                best_frog = frog;
                best_fitness = fitness;
            }
        }
    }

    return best_frog;
}

std::vector<bool> generate_random_frog(size_t size) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::vector<bool> frog(size);
    for (size_t i = 0; i < size; ++i) {
        frog[i] = std::uniform_int_distribution<>(0, 1)(gen);
    }
    return frog;
}
#include "predictor.h"
#include <vector>
#include <cstdint>

HawkeyePredictor::HawkeyePredictor(std::size_t num_entries, int counter_bits)

:entries(num_entries),
bits(counter_bits),
table(num_entries,1 << (counter_bits - 1))

{}

std::size_t HawkeyePredictor::hash_pc(std::uint64_t pc) const {
    std::uint64_t hash = pc ^ (pc >> 12);
    return hash & (entries - 1);
}

void HawkeyePredictor::train(std::uint64_t pc, bool opt_hit) {
    std::size_t index = hash_pc(pc);

    int max_value = (1 << bits) - 1;

    if (opt_hit) {
        if (table[index] < max_value)
            table[index]++;
    } else {
        if (table[index] > 0)
            table[index]--;
    }
}  

bool HawkeyePredictor::predict (std::uint64_t pc) const{
    std::size_t index = hash_pc(pc);
    return table[index] >= 4;
}

int HawkeyePredictor:: get_counter(std::uint64_t pc) const{
    std::size_t index = hash_pc(pc);
    return table[index];
}




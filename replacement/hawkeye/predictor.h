#ifndef PREDICTOR_H
#define PREDICTOR_H

#include <cstddef>     
#include <cstdint>     

#include <vector>



class HawkeyePredictor {
public:

HawkeyePredictor(std::size_t num_entries = 8192, int counter_bits = 3);

void train(std::uint64_t pc, bool opt_hit);

bool predict(std::uint64_t pc) const;

int get_counter(std::uint64_t pc) const;

private:
std::size_t hash_pc(std::uint64_t pc) const;
std::vector<int>table;
std::size_t entries;
int bits;
};

#endif
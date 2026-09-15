#ifndef OPTGEN_H
#define OPTGEN_H

#include <cstddef>     
#include <cstdint>  
#include <vector>
#include <deque>
#include <map>

class OPTgen {
public:

OPTgen(std::size_t num_sets, std::size_t associativity,std::size_t history_multiplier = 8);

bool access(std::size_t set_idx, uint64_t address);

private:
    

    std::size_t num_sets;
    std::size_t associativity;
    std::size_t history_length;   

    std::vector<std::deque<int>> occupancy_vectors; 
    std::vector<int> current_timestamp;


    std::vector<std::map<uint64_t, int>> last_access_time;

};

#endif
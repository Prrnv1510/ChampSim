#include "optgen.h"

OPTgen::OPTgen(std::size_t num_sets, std::size_t associativity,std::size_t history_multiplier)
:num_sets(num_sets),
associativity(associativity),
history_length(associativity*history_multiplier),
occupancy_vectors(num_sets,std::deque<int>(history_length,0)),
current_timestamp(num_sets,0),
last_access_time(num_sets)

{
}

bool OPTgen::access(std::size_t set_idx, uint64_t address){
    int cur_time = current_timestamp[set_idx];
    std::size_t curr_idx = cur_time%history_length;
    occupancy_vectors[set_idx][curr_idx] = 0;

    if(last_access_time[set_idx].find(address) == last_access_time[set_idx].end()){

        last_access_time[set_idx][address] = cur_time;
        current_timestamp[set_idx]++;
        return false;
    }

    int prev_time = last_access_time[set_idx][address];
    bool opt_hit = true;

    for (int t = prev_time; t < cur_time; t++)
    {
        std::size_t idx = t % history_length;

        if (occupancy_vectors[set_idx][idx] >= associativity)
        {
            opt_hit = false;
            break;
        }
    }

    if (opt_hit)
    {
        for (int t = prev_time; t < cur_time; t++)
        {
            std::size_t idx = t % history_length;
            occupancy_vectors[set_idx][idx]++;
        }
    }

    last_access_time[set_idx][address] = cur_time;
    current_timestamp[set_idx]++;

    return opt_hit;

}

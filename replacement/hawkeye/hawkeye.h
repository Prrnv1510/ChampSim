// hawkeye.h
#ifndef HAWKEYE_H
#define HAWKEYE_H
#include <vector>
#include "modules.h"
#include "optgen.h"
#include "predictor.h"
#include<unordered_map>


#include "rrip.h"
struct hawkeye : public champsim::modules::replacement {
private:
    
    OPTgen optgen;
    HawkeyePredictor predictor;
    
    std::vector<std::unordered_map<uint64_t,uint64_t>> line_pc;

    std::vector<std::vector<int>> rrpv;

    
public:
    
    explicit hawkeye(CACHE* cache);
    hawkeye(CACHE* cache, long sets, long ways);
    
    long find_victim(
        uint32_t cpu,
        uint64_t instr_id,
        long set,
        const champsim::cache_block* current_set,
        champsim::address ip,
        champsim::address full_addr,
        access_type type
    );

    void replacement_cache_fill(
        uint32_t cpu,
        long set,
        long way,
        champsim::address full_addr,
        champsim::address ip,
        champsim::address victim_addr,
        access_type type
    ) ;

    void update_replacement_state(
        uint32_t cpu,
        long set,
        long way,
        champsim::address full_addr,
        champsim::address ip,
        access_type type,
        bool hit
    );
};
#endif
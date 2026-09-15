
#include "hawkeye.h"
#include <algorithm>
#include "cache.h"

using namespace champsim;
hawkeye::hawkeye(CACHE* cache)
    : hawkeye(cache, cache -> NUM_SET, cache-> NUM_WAY)
    {}




hawkeye::hawkeye(CACHE* cache, long sets, long ways)
    : replacement(cache),
      optgen(sets,ways),
      predictor(),
      
      line_pc((sets)),
      rrpv(sets, std::vector<int>(ways, 7))
{
}



long hawkeye::find_victim(
    uint32_t cpu,
        uint64_t instr_id,
        long set,
        const champsim::cache_block* current_set,
        champsim::address ip,
        champsim::address full_addr,
        access_type type)
{
    return ::find_victim(rrpv[set]);
}

void hawkeye::replacement_cache_fill(uint32_t cpu,
        long set,
        long way,
        champsim::address full_addr,
        champsim::address ip,
        champsim::address victim_addr,
        access_type type)
{
    uint64_t pc = ip.to<uint64_t>();

    Classification cls = predictor.predict(pc) ?
        Classification::CACHE_FRIENDLY :
        Classification::CACHE_AVERSE;

    update_rrpv(rrpv[set], way, cls, false);
    
}

void hawkeye::update_replacement_state(
    uint32_t cpu,
        long set,
        long way,
        champsim::address full_addr,
        champsim::address ip,
        access_type type,
        bool hit)
{
   
    std::size_t set_idx = static_cast<std::size_t>(set);

    uint64_t pc = ip.to<uint64_t>();

    uint64_t addr = (full_addr.to<uint64_t>() )>> 6;

    auto it = line_pc[set_idx].find(addr);

    bool had_previous_access = (it != line_pc[set_idx].end());

    uint64_t previous_pc = 0;

    if (had_previous_access)
        previous_pc = it->second;

    bool opt_hit = optgen.access(set_idx, addr);

    
    if(had_previous_access)
        predictor.train(previous_pc, opt_hit);

    
    line_pc[set_idx][addr] = pc;

    if (hit)
    {
        Classification cls =predictor.predict(pc)? Classification::CACHE_FRIENDLY: Classification::CACHE_AVERSE;

        update_rrpv(rrpv[set_idx],way,cls,true);
    }
}
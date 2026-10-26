#include "math_bits.hpp"
#include <array>
#include <cassert>
#include <utility>
#include <vector>
using Writes = std::vector<std::pair<std::uint32_t,std::uint64_t>>;
static void record(void* context,std::uint32_t address,std::uint64_t value) {
    static_cast<Writes*>(context)->emplace_back(address,value);
}
int main() {
    std::array<std::uint64_t,7> memory{};
    memory.front()=0x12345678;memory.back()=0x87654321;
    auto* environment=memory.data()+1;
    assert(hm_00100310(environment,0,640,224,0,0,1,2,1));
    assert(environment[0]==0x66 && environment[1]==3 && environment[2]==5120);
    Writes writes;
    assert(hm_00100580(environment,27,record,&writes));
    const std::array<std::uint32_t,5> addresses={0x12000000,0x12000020,0x12000090,0x120000a0,0x120000e0};
    assert(writes.size()==5);
    for(unsigned i=0;i<5;i++) {assert(writes[i].first==addresses[i]);assert(writes[i].second==environment[i]);}
    const auto saved=memory;
    assert(!hm_00100310(environment,0,0,224,0,0,1,2,1));assert(memory==saved);
    assert(!hm_00100580(nullptr,27,record,&writes));assert(writes.size()==5);
    assert(!hm_00100580(environment,27,nullptr,&writes));assert(writes.size()==5);
    assert(memory.front()==0x12345678 && memory.back()==0x87654321);
    assert(hm_00100640(0,640,224,1)==70);
    assert(hm_00100640(0,640,224,3)==140);
}

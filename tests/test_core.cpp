#include <cassert>
#include <cstring>
#include <iostream>
#include "../firmware/gps_display/status.h"

int main() {
    using atlas::State;
    using atlas::classify;
    assert(classify(false, 0, false, 0) == State::NoData);
    assert(classify(false, 30000, true, 0) == State::NoData);
    assert(classify(true, 0, false, 0) == State::Waiting);
    assert(classify(true, 2000, false, 0) == State::Waiting);
    assert(classify(true, 2001, false, 0) == State::Stale);
    assert(classify(true, 0, true, 0) == State::RecentPosition);
    assert(classify(true, 0, true, 5000) == State::RecentPosition);
    assert(classify(true, 0, true, 5001) == State::Stale);
    assert(classify(true, 2001, true, 0) == State::Stale);
    assert(classify(true, 0, false, UINT32_MAX) == State::Waiting);
    assert(classify(true, 0, true, UINT32_MAX) == State::Stale);
    assert(classify(true, 100, true, 100, 100, 100) == State::RecentPosition);
    assert(!atlas::due(99, 0, 100));
    assert(atlas::due(100, 0, 100));
    assert(atlas::due(20, UINT32_MAX - 99, 120));
    assert(!atlas::due(20, UINT32_MAX - 99, 121));
    assert(std::strcmp(atlas::label(State::Stale), "DATA / POSITION STALE") == 0);
    std::cout << "17 Atlas state/freshness checks passed; no hardware test.\n";
}

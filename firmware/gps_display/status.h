#pragma once
#include <stdint.h>

namespace atlas {
enum class State { NoData, Waiting, RecentPosition, Stale };

inline State classify(bool seenBytes, uint32_t byteAge, bool positionValid,
                      uint32_t positionAge, uint32_t byteLimit = 2000,
                      uint32_t positionLimit = 5000) {
    if (!seenBytes) return State::NoData;
    if (byteAge > byteLimit) return State::Stale;
    if (!positionValid) return State::Waiting;
    return positionAge <= positionLimit ? State::RecentPosition : State::Stale;
}

inline bool due(uint32_t now, uint32_t before, uint32_t interval) {
    return static_cast<uint32_t>(now - before) >= interval;
}

inline const char* label(State state) {
    switch (state) {
    case State::NoData: return "NO DATA";
    case State::Waiting: return "WAITING FOR POSITION";
    case State::RecentPosition: return "RECENT POSITION";
    case State::Stale: return "DATA / POSITION STALE";
    }
    return "UNKNOWN";
}
}

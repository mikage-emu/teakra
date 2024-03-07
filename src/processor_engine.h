#pragma once

#include <cstdint>

namespace Teakra {

class ProcessorEngine {
public:
    virtual ~ProcessorEngine() = default;

    virtual void Reset() = 0;
    virtual void Run(uint64_t cycles) = 0;
    virtual void SignalInterrupt(uint32_t i) = 0;
    virtual void SignalVectoredInterrupt(uint32_t address, bool context_switch) = 0;
};

} // namespace Teakra

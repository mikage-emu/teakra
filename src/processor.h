#pragma once

#include <memory>
#include "common_types.h"
#include "core_timing.h"
#include "processor_engine.h"

namespace Teakra {

class MemoryInterface;

using ProcessorEngineFactory = std::unique_ptr<ProcessorEngine>(*)(CoreTiming&, struct RegisterState&, MemoryInterface&);

class Processor {
public:
    Processor(CoreTiming&, MemoryInterface&, const ProcessorEngineFactory&);
    ~Processor();

    void Reset();
    void Run(unsigned cycles);
    void SignalInterrupt(u32 i);
    void SignalVectoredInterrupt(u32 address, bool context_switch);

    struct Impl;
private:
    std::unique_ptr<Impl> impl;
};

} // namespace Teakra

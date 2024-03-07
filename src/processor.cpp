#include "interpreter.h"
#include "processor.h"
#include "register.h"

namespace Teakra {

std::unique_ptr<ProcessorEngine> CreateInterpreterEngine(CoreTiming& core_timing, struct RegisterState& regs, MemoryInterface& memory_interface) {
    return std::make_unique<Interpreter>(core_timing, regs, memory_interface);
}

struct Processor::Impl {
    Impl(CoreTiming& core_timing, MemoryInterface& memory_interface, const ProcessorEngineFactory& engine_factory)
        : core_timing(core_timing),
        memory_interface(memory_interface),
        engine(engine_factory(core_timing, regs, memory_interface))
        {}
    virtual ~Impl() = default;

    CoreTiming& core_timing;
    RegisterState regs;

    MemoryInterface& memory_interface;

    std::unique_ptr<ProcessorEngine> engine;
};

void Processor::Reset() {
    impl->regs = RegisterState();
    impl->engine->Reset();
}

Processor::Processor(CoreTiming& core_timing, MemoryInterface& memory_interface, const ProcessorEngineFactory& engine_factory)
    : impl(new Impl(core_timing, memory_interface, engine_factory
    )) {}
Processor::~Processor() = default;

void Processor::Run(unsigned cycles) {
    impl->engine->Run(cycles);
}

void Processor::SignalInterrupt(u32 i) {
    impl->engine->SignalInterrupt(i);
}
void Processor::SignalVectoredInterrupt(u32 address, bool context_switch) {
    impl->engine->SignalVectoredInterrupt(address, context_switch);
}

} // namespace Teakra

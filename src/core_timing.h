#pragma once

#include <algorithm>
#include <functional>
#include <limits>
#include <vector>
#include "common_types.h"

namespace Teakra {

class CoreTiming {
public:
    class Callbacks {
    public:
        virtual ~Callbacks() = default;
        virtual void Tick(uint32_t cycles) = 0;
        virtual u64 GetMaxSkip() const = 0;
        virtual void Skip(u64) = 0;
        static constexpr u64 Infinity = std::numeric_limits<u64>::max();
    };

    void Tick(uint32_t cycles) {
        for (const auto& callbacks : registered_callbacks) {
            callbacks->Tick(cycles);
        }
    }

    u64 Skip(u64 maximum) {
        u64 ticks = maximum;
        for (const auto& callbacks : registered_callbacks) {
            ticks = std::min(ticks, callbacks->GetMaxSkip());
        }
        for (const auto& callbacks : registered_callbacks) {
            callbacks->Skip(ticks);
        }
        return ticks;
    }

    u64 GetMaxSkip() const {
        u64 ticks = Callbacks::Infinity;
        for (const auto& callbacks : registered_callbacks) {
            ticks = std::min(ticks, callbacks->GetMaxSkip());
        }
        return ticks;
    }

    void RegisterCallbacks(Callbacks* callbacks) {
        registered_callbacks.push_back(std::move(callbacks));
    }

private:
    std::vector<Callbacks*> registered_callbacks;
};
} // namespace Teakra

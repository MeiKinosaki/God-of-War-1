#pragma once

#include <array>
#include <cstdint>

namespace gow1 {
namespace ee {

// The EE GPRs are 128-bit. Store them as two 64-bit halves without relying
// on compiler-specific 128-bit integer extensions.
struct Register128 {
    std::uint64_t low;
    std::uint64_t high;

    Register128(std::uint64_t low_value = 0, std::uint64_t high_value = 0) noexcept
        : low(low_value), high(high_value) {}
};

struct CpuState {
    std::array<Register128, 32> gpr{};
    std::uint32_t pc = 0;
    std::uint64_t hi = 0;
    std::uint64_t lo = 0;
    std::uint64_t hi1 = 0;
    std::uint64_t lo1 = 0;
    std::uint32_t status = 0;
    std::uint32_t cause = 0;
    std::uint32_t epc = 0;

    Register128 read_gpr(std::uint8_t index) const noexcept {
        return index == 0 || index >= gpr.size() ? Register128{} : gpr[index];
    }

    void write_gpr(std::uint8_t index, Register128 value) noexcept {
        if (index != 0 && index < gpr.size()) {
            gpr[index] = value;
        }
        gpr[0] = Register128{};
    }
};

} // namespace ee
} // namespace gow1

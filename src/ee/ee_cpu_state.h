#pragma once

#include <array>
#include <cstdint>

namespace gow1::ee {

// The EE GPRs are 128-bit. Represent them as two 64-bit halves so this
// portable scaffold does not depend on compiler-specific 128-bit integers.
struct Register128 {
    std::uint64_t low = 0;
    std::uint64_t high = 0;
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

} // namespace gow1::ee

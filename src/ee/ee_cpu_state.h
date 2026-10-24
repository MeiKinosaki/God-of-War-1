#pragma once

#include <array>
#include <cstdint>

namespace gow1::ee {

// Architectural state container only; instruction execution is not implemented.
struct CpuState {
    std::array<std::uint64_t, 32> gpr{};
    std::uint32_t pc = 0;
    std::uint32_t hi = 0;
    std::uint32_t lo = 0;
    std::uint32_t status = 0;
    std::uint32_t cause = 0;
    std::uint32_t epc = 0;

    // Register zero is hardwired to zero on MIPS-family CPUs.
    std::uint64_t read_gpr(std::uint8_t index) const noexcept {
        return index == 0 || index >= gpr.size() ? 0 : gpr[index];
    }

    void write_gpr(std::uint8_t index, std::uint64_t value) noexcept {
        if (index != 0 && index < gpr.size()) {
            gpr[index] = value;
        }
        gpr[0] = 0;
    }
};

} // namespace gow1::ee

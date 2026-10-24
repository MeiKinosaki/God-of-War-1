#pragma once

#include <cstdint>

#include "ee_cpu_state.h"

namespace gow1 {
namespace ee {

// Initial, isolated ALU helpers. This is not yet an instruction decoder or
// complete R5900 interpreter. Operations currently cover the low 64-bit lane.
inline void op_addu(CpuState& cpu, std::uint8_t rd,
                    std::uint8_t rs, std::uint8_t rt) noexcept {
    const std::uint64_t result = cpu.read_gpr(rs).low + cpu.read_gpr(rt).low;
    cpu.write_gpr(rd, Register128(result, 0));
}

inline void op_and(CpuState& cpu, std::uint8_t rd,
                   std::uint8_t rs, std::uint8_t rt) noexcept {
    cpu.write_gpr(rd, Register128(cpu.read_gpr(rs).low & cpu.read_gpr(rt).low, 0));
}

inline void op_or(CpuState& cpu, std::uint8_t rd,
                  std::uint8_t rs, std::uint8_t rt) noexcept {
    cpu.write_gpr(rd, Register128(cpu.read_gpr(rs).low | cpu.read_gpr(rt).low, 0));
}

inline void op_xor(CpuState& cpu, std::uint8_t rd,
                   std::uint8_t rs, std::uint8_t rt) noexcept {
    cpu.write_gpr(rd, Register128(cpu.read_gpr(rs).low ^ cpu.read_gpr(rt).low, 0));
}

inline void op_nor(CpuState& cpu, std::uint8_t rd,
                   std::uint8_t rs, std::uint8_t rt) noexcept {
    cpu.write_gpr(rd, Register128(~(cpu.read_gpr(rs).low | cpu.read_gpr(rt).low), 0));
}

inline void op_andi(CpuState& cpu, std::uint8_t rt,
                    std::uint8_t rs, std::uint16_t immediate) noexcept {
    cpu.write_gpr(rt, Register128(cpu.read_gpr(rs).low & immediate, 0));
}

inline void op_ori(CpuState& cpu, std::uint8_t rt,
                   std::uint8_t rs, std::uint16_t immediate) noexcept {
    cpu.write_gpr(rt, Register128(cpu.read_gpr(rs).low | immediate, 0));
}

inline void op_xori(CpuState& cpu, std::uint8_t rt,
                    std::uint8_t rs, std::uint16_t immediate) noexcept {
    cpu.write_gpr(rt, Register128(cpu.read_gpr(rs).low ^ immediate, 0));
}

} // namespace ee
} // namespace gow1

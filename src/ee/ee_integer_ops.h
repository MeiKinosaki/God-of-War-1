#pragma once

#include <cstdint>

#include "ee_cpu_state.h"

namespace gow1 {
namespace ee {

// Initial 64-bit-lane helpers for unit testing. These do not constitute a
// complete R5900 decoder; exact EE 32/64/128-bit semantics remain to be wired
// in instruction-by-instruction.
inline void op_addu(CpuState& cpu, std::uint8_t rd,
                    std::uint8_t rs, std::uint8_t rt) noexcept {
    cpu.write_gpr(rd, Register128(cpu.read_gpr(rs).low + cpu.read_gpr(rt).low, 0));
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
inline void op_addiu(CpuState& cpu, std::uint8_t rt,
                     std::uint8_t rs, std::uint16_t immediate) noexcept {
    const std::int32_t signed_immediate = static_cast<std::int16_t>(immediate);
    const std::uint32_t result =
        static_cast<std::uint32_t>(cpu.read_gpr(rs).low) +
        static_cast<std::uint32_t>(signed_immediate);
    cpu.write_gpr(rt, Register128(static_cast<std::uint64_t>(
        static_cast<std::int64_t>(static_cast<std::int32_t>(result))), 0));
}

inline void op_sll(CpuState& cpu, std::uint8_t rd,
                   std::uint8_t rt, std::uint8_t shift) noexcept {
    const std::uint32_t value = static_cast<std::uint32_t>(cpu.read_gpr(rt).low);
    const std::uint32_t result = shift < 32 ? value << shift : 0;
    cpu.write_gpr(rd, Register128(static_cast<std::uint64_t>(
        static_cast<std::int64_t>(static_cast<std::int32_t>(result))), 0));
}
inline void op_srl(CpuState& cpu, std::uint8_t rd,
                   std::uint8_t rt, std::uint8_t shift) noexcept {
    const std::uint32_t value = static_cast<std::uint32_t>(cpu.read_gpr(rt).low);
    const std::uint32_t result = shift < 32 ? value >> shift : 0;
    cpu.write_gpr(rd, Register128(static_cast<std::uint64_t>(
        static_cast<std::int64_t>(static_cast<std::int32_t>(result))), 0));
}
inline void op_slt(CpuState& cpu, std::uint8_t rd,
                   std::uint8_t rs, std::uint8_t rt) noexcept {
    const auto lhs = static_cast<std::int64_t>(cpu.read_gpr(rs).low);
    const auto rhs = static_cast<std::int64_t>(cpu.read_gpr(rt).low);
    cpu.write_gpr(rd, Register128(lhs < rhs ? 1u : 0u, 0));
}
inline void op_sltu(CpuState& cpu, std::uint8_t rd,
                    std::uint8_t rs, std::uint8_t rt) noexcept {
    cpu.write_gpr(rd, Register128(
        cpu.read_gpr(rs).low < cpu.read_gpr(rt).low ? 1u : 0u, 0));
}

} // namespace ee
} // namespace gow1

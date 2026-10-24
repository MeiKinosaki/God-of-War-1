#pragma once

#include <cstdint>

#include "ee_cpu_state.h"

namespace gow1 {
namespace ee {

// Initial 32-bit MIPS-like helper semantics for unit tests. These helpers
// are not a complete Emotion Engine implementation. EE-specific 64/128-bit
// operations, instruction decode, exceptions, and delay slots remain pending.
inline std::uint32_t word_result(std::uint32_t value) noexcept {
    return value;
}

inline void write_word_result(CpuState& cpu, std::uint8_t rd,
                              std::uint32_t value) noexcept {
    const std::int32_t signed_value = static_cast<std::int32_t>(value);
    cpu.write_gpr(rd, Register128(static_cast<std::uint64_t>(
        static_cast<std::int64_t>(signed_value)), 0));
}

inline void op_addu(CpuState& cpu, std::uint8_t rd,
                    std::uint8_t rs, std::uint8_t rt) noexcept {
    const auto result = static_cast<std::uint32_t>(cpu.read_gpr(rs).low) +
                        static_cast<std::uint32_t>(cpu.read_gpr(rt).low);
    write_word_result(cpu, rd, result);
}
inline void op_and(CpuState& cpu, std::uint8_t rd,
                   std::uint8_t rs, std::uint8_t rt) noexcept {
    write_word_result(cpu, rd, static_cast<std::uint32_t>(
        cpu.read_gpr(rs).low & cpu.read_gpr(rt).low));
}
inline void op_or(CpuState& cpu, std::uint8_t rd,
                  std::uint8_t rs, std::uint8_t rt) noexcept {
    write_word_result(cpu, rd, static_cast<std::uint32_t>(
        cpu.read_gpr(rs).low | cpu.read_gpr(rt).low));
}
inline void op_xor(CpuState& cpu, std::uint8_t rd,
                   std::uint8_t rs, std::uint8_t rt) noexcept {
    write_word_result(cpu, rd, static_cast<std::uint32_t>(
        cpu.read_gpr(rs).low ^ cpu.read_gpr(rt).low));
}
inline void op_nor(CpuState& cpu, std::uint8_t rd,
                   std::uint8_t rs, std::uint8_t rt) noexcept {
    write_word_result(cpu, rd, static_cast<std::uint32_t>(
        ~(cpu.read_gpr(rs).low | cpu.read_gpr(rt).low)));
}
inline void op_andi(CpuState& cpu, std::uint8_t rt,
                    std::uint8_t rs, std::uint16_t immediate) noexcept {
    write_word_result(cpu, rt, static_cast<std::uint32_t>(
        cpu.read_gpr(rs).low) & immediate);
}
inline void op_ori(CpuState& cpu, std::uint8_t rt,
                   std::uint8_t rs, std::uint16_t immediate) noexcept {
    write_word_result(cpu, rt, static_cast<std::uint32_t>(
        cpu.read_gpr(rs).low) | immediate);
}
inline void op_xori(CpuState& cpu, std::uint8_t rt,
                    std::uint8_t rs, std::uint16_t immediate) noexcept {
    write_word_result(cpu, rt, static_cast<std::uint32_t>(
        cpu.read_gpr(rs).low) ^ immediate);
}
inline void op_addiu(CpuState& cpu, std::uint8_t rt,
                     std::uint8_t rs, std::uint16_t immediate) noexcept {
    const std::int32_t signed_immediate = static_cast<std::int16_t>(immediate);
    const std::uint32_t result = static_cast<std::uint32_t>(cpu.read_gpr(rs).low) +
                                 static_cast<std::uint32_t>(signed_immediate);
    write_word_result(cpu, rt, result);
}
inline void op_sll(CpuState& cpu, std::uint8_t rd,
                   std::uint8_t rt, std::uint8_t shift) noexcept {
    const std::uint32_t value = static_cast<std::uint32_t>(cpu.read_gpr(rt).low);
    write_word_result(cpu, rd, value << (shift & 31u));
}
inline void op_srl(CpuState& cpu, std::uint8_t rd,
                   std::uint8_t rt, std::uint8_t shift) noexcept {
    const std::uint32_t value = static_cast<std::uint32_t>(cpu.read_gpr(rt).low);
    write_word_result(cpu, rd, value >> (shift & 31u));
}
inline void op_slt(CpuState& cpu, std::uint8_t rd,
                   std::uint8_t rs, std::uint8_t rt) noexcept {
    const auto lhs = static_cast<std::int32_t>(static_cast<std::uint32_t>(cpu.read_gpr(rs).low));
    const auto rhs = static_cast<std::int32_t>(static_cast<std::uint32_t>(cpu.read_gpr(rt).low));
    write_word_result(cpu, rd, lhs < rhs ? 1u : 0u);
}
inline void op_sltu(CpuState& cpu, std::uint8_t rd,
                    std::uint8_t rs, std::uint8_t rt) noexcept {
    const auto lhs = static_cast<std::uint32_t>(cpu.read_gpr(rs).low);
    const auto rhs = static_cast<std::uint32_t>(cpu.read_gpr(rt).low);
    write_word_result(cpu, rd, lhs < rhs ? 1u : 0u);
}

} // namespace ee
} // namespace gow1

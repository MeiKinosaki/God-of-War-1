#pragma once

#include <cstdint>

#include "ee_cpu_state.h"

namespace gow1 {
namespace ee {

// These helpers are an initial 64-bit-lane scaffold, not a full R5900
// interpreter. EE instruction-width and sign-extension rules still need
// to be implemented per instruction before this can run game code.
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

// ADDIU sign-extends its 16-bit immediate and does not trap on overflow.
// This initial helper operates on a 32-bit result lane.
inline void op_addiu(CpuState& cpu, std::uint8_t rt,
                     std::uint8_t rs, std::uint16_t immediate) noexcept {
    const std::int32_t signed_immediate = static_cast<std::int16_t>(immediate);
    const std::uint32_t result =
        static_cast<std::uint32_t>(cpu.read_gpr(rs).low) +
        static_cast<std::uint32_t>(signed_immediate);
    cpu.write_gpr(rt, Register128(static_cast<std::uint64_t>(
        static_cast<std::int64_t>(static_cast<std::int32_t>(result))), 0));
}

} // namespace ee
} // namespace gow1

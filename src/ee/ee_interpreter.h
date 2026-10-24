#pragma once

#include "ee_instruction_decode.h"
#include "ee_integer_ops.h"

namespace gow1 {
namespace ee {

// Executes only the small ALU subset currently represented by the decoder.
// PC sequencing, branches/delay slots, exceptions and EE-specific operations
// are intentionally not performed here yet.
inline bool execute_alu_instruction(CpuState& cpu, std::uint32_t raw) noexcept {
    const DecodedInstruction ins = decode_instruction(raw);
    switch (ins.kind) {
    case InstructionKind::Sll:
        op_sll(cpu, ins.rd, ins.rt, ins.shift);
        return true;
    case InstructionKind::Srl:
        op_srl(cpu, ins.rd, ins.rt, ins.shift);
        return true;
    case InstructionKind::Addu:
        op_addu(cpu, ins.rd, ins.rs, ins.rt);
        return true;
    case InstructionKind::And:
        op_and(cpu, ins.rd, ins.rs, ins.rt);
        return true;
    case InstructionKind::Or:
        op_or(cpu, ins.rd, ins.rs, ins.rt);
        return true;
    case InstructionKind::Xor:
        op_xor(cpu, ins.rd, ins.rs, ins.rt);
        return true;
    case InstructionKind::Nor:
        op_nor(cpu, ins.rd, ins.rs, ins.rt);
        return true;
    case InstructionKind::Slt:
        op_slt(cpu, ins.rd, ins.rs, ins.rt);
        return true;
    case InstructionKind::Sltu:
        op_sltu(cpu, ins.rd, ins.rs, ins.rt);
        return true;
    case InstructionKind::Addiu:
        op_addiu(cpu, ins.rt, ins.rs, ins.immediate);
        return true;
    case InstructionKind::Andi:
        op_andi(cpu, ins.rt, ins.rs, ins.immediate);
        return true;
    case InstructionKind::Ori:
        op_ori(cpu, ins.rt, ins.rs, ins.immediate);
        return true;
    case InstructionKind::Xori:
        op_xori(cpu, ins.rt, ins.rs, ins.immediate);
        return true;
    case InstructionKind::Unsupported:
    default:
        return false;
    }
}

// Executes one supported non-control-flow instruction and advances PC by 4.
// Branches, delay slots, exceptions and instruction fetch remain out of scope.
inline bool execute_instruction_step(CpuState& cpu, std::uint32_t raw) noexcept {
    if (!execute_alu_instruction(cpu, raw)) {
        return false;
    }
    cpu.pc += 4u;
    return true;
}

} // namespace ee
} // namespace gow1

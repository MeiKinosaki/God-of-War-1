#pragma once

#include <cstdint>

namespace gow1 {
namespace ee {

enum class InstructionKind {
    Sll,
    Srl,
    Addu,
    And,
    Or,
    Xor,
    Nor,
    Slt,
    Sltu,
    Addiu,
    Andi,
    Ori,
    Xori,
    Unsupported
};

struct DecodedInstruction {
    InstructionKind kind;
    std::uint8_t rs;
    std::uint8_t rt;
    std::uint8_t rd;
    std::uint8_t shift;
    std::uint16_t immediate;
    std::uint32_t raw;
};

inline DecodedInstruction decode_instruction(std::uint32_t raw) noexcept {
    const std::uint8_t opcode = static_cast<std::uint8_t>((raw >> 26) & 0x3Fu);
    const std::uint8_t rs = static_cast<std::uint8_t>((raw >> 21) & 0x1Fu);
    const std::uint8_t rt = static_cast<std::uint8_t>((raw >> 16) & 0x1Fu);
    const std::uint8_t rd = static_cast<std::uint8_t>((raw >> 11) & 0x1Fu);
    const std::uint8_t shift = static_cast<std::uint8_t>((raw >> 6) & 0x1Fu);
    const std::uint8_t funct = static_cast<std::uint8_t>(raw & 0x3Fu);
    const std::uint16_t immediate = static_cast<std::uint16_t>(raw & 0xFFFFu);

    InstructionKind kind = InstructionKind::Unsupported;
    if (opcode == 0) {
        switch (funct) {
        case 0x00: kind = InstructionKind::Sll; break;
        case 0x02: kind = InstructionKind::Srl; break;
        case 0x21: kind = InstructionKind::Addu; break;
        case 0x24: kind = InstructionKind::And; break;
        case 0x25: kind = InstructionKind::Or; break;
        case 0x26: kind = InstructionKind::Xor; break;
        case 0x27: kind = InstructionKind::Nor; break;
        case 0x2A: kind = InstructionKind::Slt; break;
        case 0x2B: kind = InstructionKind::Sltu; break;
        default: break;
        }
    } else {
        switch (opcode) {
        case 0x09: kind = InstructionKind::Addiu; break;
        case 0x0C: kind = InstructionKind::Andi; break;
        case 0x0D: kind = InstructionKind::Ori; break;
        case 0x0E: kind = InstructionKind::Xori; break;
        default: break;
        }
    }

    return {kind, rs, rt, rd, shift, immediate, raw};
}

} // namespace ee
} // namespace gow1

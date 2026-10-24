#include "../src/ee/ee_instruction_decode.h"

#include <cassert>
#include <cstdint>

static std::uint32_t encode_r(std::uint8_t rs, std::uint8_t rt,
                              std::uint8_t rd, std::uint8_t shift,
                              std::uint8_t funct) {
    return (static_cast<std::uint32_t>(rs) << 21) |
           (static_cast<std::uint32_t>(rt) << 16) |
           (static_cast<std::uint32_t>(rd) << 11) |
           (static_cast<std::uint32_t>(shift) << 6) | funct;
}

int main() {
    using gow1::ee::InstructionKind;
    auto r = gow1::ee::decode_instruction(encode_r(3, 4, 5, 6, 0x21));
    assert(r.kind == InstructionKind::Addu);
    assert(r.rs == 3 && r.rt == 4 && r.rd == 5 && r.shift == 6);

    auto shift = gow1::ee::decode_instruction(encode_r(0, 7, 8, 9, 0x02));
    assert(shift.kind == InstructionKind::Srl);
    assert(shift.rt == 7 && shift.rd == 8 && shift.shift == 9);

    const std::uint32_t addiu = (0x09u << 26) | (2u << 21) | (3u << 16) | 0xFFFEu;
    auto i = gow1::ee::decode_instruction(addiu);
    assert(i.kind == InstructionKind::Addiu);
    assert(i.rs == 2 && i.rt == 3 && i.immediate == 0xFFFEu);

    auto unknown = gow1::ee::decode_instruction(0xFFFFFFFFu);
    assert(unknown.kind == InstructionKind::Unsupported);
    return 0;
}

#include "../src/ee/ee_interpreter.h"

#include <cassert>
#include <cstdint>

int main() {
    gow1::ee::CpuState cpu{};
    cpu.write_gpr(1, gow1::ee::Register128(7, 0));
    cpu.write_gpr(2, gow1::ee::Register128(9, 0));

    // ADDU r3, r1, r2
    const std::uint32_t addu =
        (1u << 21) | (2u << 16) | (3u << 11) | 0x21u;
    assert(gow1::ee::execute_alu_instruction(cpu, addu));
    assert(cpu.read_gpr(3).low == 16);

    // ADDIU r4, r3, -1
    const std::uint32_t addiu =
        (0x09u << 26) | (3u << 21) | (4u << 16) | 0xFFFFu;
    assert(gow1::ee::execute_alu_instruction(cpu, addiu));
    assert(cpu.read_gpr(4).low == 15);

    // Unsupported encoding must be reported rather than treated as executed.
    assert(!gow1::ee::execute_alu_instruction(cpu, 0xFFFFFFFFu));
    assert(cpu.read_gpr(0).low == 0);
    return 0;
}

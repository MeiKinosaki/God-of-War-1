#include "../src/ee/ee_integer_ops.h"

#include <cassert>
#include <cstdint>

int main() {
    gow1::ee::CpuState cpu{};
    cpu.write_gpr(1, gow1::ee::Register128(0xF0F0u, 0x1234u));
    cpu.write_gpr(2, gow1::ee::Register128(0x0FF0u, 0x5678u));

    gow1::ee::op_addu(cpu, 3, 1, 2);
    assert(cpu.read_gpr(3).low == 0x100E0u);
    assert(cpu.read_gpr(3).high == 0);
    gow1::ee::op_and(cpu, 4, 1, 2);
    assert(cpu.read_gpr(4).low == 0x00F0u);
    gow1::ee::op_or(cpu, 5, 1, 2);
    assert(cpu.read_gpr(5).low == 0xFFF0u);
    gow1::ee::op_xor(cpu, 6, 1, 2);
    assert(cpu.read_gpr(6).low == 0xFF00u);
    gow1::ee::op_nor(cpu, 7, 1, 2);
    assert(cpu.read_gpr(7).low == ~std::uint64_t(0xFFF0u));
    gow1::ee::op_andi(cpu, 8, 1, 0x00FFu);
    assert(cpu.read_gpr(8).low == 0x00F0u);
    gow1::ee::op_ori(cpu, 9, 2, 0xF000u);
    assert(cpu.read_gpr(9).low == 0xFFF0u);
    gow1::ee::op_xori(cpu, 10, 1, 0xFFFFu);
    assert(cpu.read_gpr(10).low == (0xF0F0u ^ 0xFFFFu));
    gow1::ee::op_addiu(cpu, 11, 1, 0xFFFFu);
    assert(cpu.read_gpr(11).low == 0xF0EFu);

    cpu.write_gpr(12, gow1::ee::Register128(1, 0));
    gow1::ee::op_addiu(cpu, 13, 12, 0xFFFFu);
    assert(cpu.read_gpr(13).low == 0);

    cpu.write_gpr(14, gow1::ee::Register128(0x80000000u, 0));
    gow1::ee::op_sll(cpu, 15, 14, 1);
    assert(cpu.read_gpr(15).low == 0);
    gow1::ee::op_srl(cpu, 16, 14, 1);
    assert(cpu.read_gpr(16).low == 0x40000000u);

    cpu.write_gpr(17, gow1::ee::Register128(static_cast<std::uint64_t>(-1), 0));
    cpu.write_gpr(18, gow1::ee::Register128(1, 0));
    gow1::ee::op_slt(cpu, 19, 17, 18);
    assert(cpu.read_gpr(19).low == 1);
    gow1::ee::op_sltu(cpu, 20, 17, 18);
    assert(cpu.read_gpr(20).low == 0);

    gow1::ee::op_addu(cpu, 0, 1, 2);
    assert(cpu.read_gpr(0).low == 0);
    assert(cpu.read_gpr(0).high == 0);
    return 0;
}

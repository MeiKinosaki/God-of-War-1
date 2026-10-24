#include "../src/ee/ee_cpu_state.h"

#include <cassert>
#include <cstdint>

int main() {
    gow1::ee::CpuState cpu{};
    assert(cpu.pc == 0);
    assert(cpu.read_gpr(0).low == 0);
    assert(cpu.read_gpr(0).high == 0);

    cpu.write_gpr(0, {0xFFFFFFFFFFFFFFFFull, 0xFFFFFFFFFFFFFFFFull});
    assert(cpu.read_gpr(0).low == 0);
    assert(cpu.read_gpr(0).high == 0);

    cpu.write_gpr(1, {0x0123456789ABCDEFull, 0xFEDCBA9876543210ull});
    assert(cpu.read_gpr(1).low == 0x0123456789ABCDEFull);
    assert(cpu.read_gpr(1).high == 0xFEDCBA9876543210ull);

    cpu.write_gpr(31, {0x55u, 0xAAu});
    assert(cpu.read_gpr(31).low == 0x55u);
    assert(cpu.read_gpr(31).high == 0xAAu);

    cpu.write_gpr(32, {0xAAu, 0xBBu});
    assert(cpu.read_gpr(32).low == 0);
    assert(cpu.read_gpr(32).high == 0);
    return 0;
}

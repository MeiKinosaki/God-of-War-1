#include "../src/ee/ee_cpu_state.h"

#include <cassert>
#include <cstdint>

int main() {
    gow1::ee::CpuState cpu{};
    assert(cpu.pc == 0);
    assert(cpu.read_gpr(0) == 0);

    cpu.write_gpr(0, 0xFFFFFFFFFFFFFFFFull);
    assert(cpu.read_gpr(0) == 0);

    cpu.write_gpr(1, 0x0123456789ABCDEFull);
    assert(cpu.read_gpr(1) == 0x0123456789ABCDEFull);

    cpu.write_gpr(31, 0x55u);
    assert(cpu.read_gpr(31) == 0x55u);

    // Invalid register indices are handled defensively.
    cpu.write_gpr(32, 0xAAu);
    assert(cpu.read_gpr(32) == 0);
    return 0;
}

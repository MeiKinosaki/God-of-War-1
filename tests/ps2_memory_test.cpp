#include "../src/common/ps2_memory.h"

#include <cassert>
#include <cstdint>

int main() {
    std::uint8_t bytes[4] = {0, 0, 0, 0};

    gow1::write_le16(bytes, 0xA1B2u);
    assert(bytes[0] == 0xB2u && bytes[1] == 0xA1u);
    assert(gow1::read_le16(bytes) == 0xA1B2u);

    gow1::write_le32(bytes, 0x1234ABCDu);
    assert(bytes[0] == 0xCDu && bytes[1] == 0xABu);
    assert(bytes[2] == 0x34u && bytes[3] == 0x12u);
    assert(gow1::read_le32(bytes) == 0x1234ABCDu);

    assert(gow1::range_fits(0, 0, 1024));
    assert(gow1::range_fits(1020, 4, 1024));
    assert(!gow1::range_fits(1021, 4, 1024));
    assert(!gow1::range_fits(1025, 0, 1024));
    assert(!gow1::range_fits(0xFFFFFFF0u, 0x40u, 0xFFFFFFFFu));
    return 0;
}

#pragma once

#include <cstddef>
#include <cstdint>

namespace gow1 {

// The PS2 Emotion Engine and IOP are little-endian. These helpers make that
// contract explicit and avoid alignment/aliasing assumptions in host tests.
inline std::uint16_t read_le16(const std::uint8_t* p) noexcept {
    return static_cast<std::uint16_t>(p[0]) |
           (static_cast<std::uint16_t>(p[1]) << 8);
}

inline std::uint32_t read_le32(const std::uint8_t* p) noexcept {
    return static_cast<std::uint32_t>(p[0]) |
           (static_cast<std::uint32_t>(p[1]) << 8) |
           (static_cast<std::uint32_t>(p[2]) << 16) |
           (static_cast<std::uint32_t>(p[3]) << 24);
}

inline void write_le16(std::uint8_t* p, std::uint16_t value) noexcept {
    p[0] = static_cast<std::uint8_t>(value);
    p[1] = static_cast<std::uint8_t>(value >> 8);
}

inline void write_le32(std::uint8_t* p, std::uint32_t value) noexcept {
    p[0] = static_cast<std::uint8_t>(value);
    p[1] = static_cast<std::uint8_t>(value >> 8);
    p[2] = static_cast<std::uint8_t>(value >> 16);
    p[3] = static_cast<std::uint8_t>(value >> 24);
}

// Validate [address, address + length) without allowing unsigned overflow.
inline bool range_fits(std::uint32_t address,
                       std::uint32_t length,
                       std::uint32_t memory_size) noexcept {
    return address <= memory_size && length <= memory_size - address;
}

} // namespace gow1

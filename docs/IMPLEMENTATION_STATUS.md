# Implementation status — God of War 1 → Xbox 360 RGH

## Implemented source
- Portable C++11 little-endian 16/32-bit memory access helpers and overflow-safe range checks.
- Initial Emotion Engine CPU state container with 128-bit GPR storage represented as two 64-bit halves.
- Initial 32-bit-lane ALU helpers: ADDU, AND, OR, XOR, NOR, ANDI, ORI, XORI, ADDIU, SLL, SRL, SLT and SLTU.
- Initial instruction-field decoder for a small supported subset of R-type and I-type MIPS-like encodings, with unsupported instructions classified explicitly.
- Initial ALU dispatch layer that decodes and executes the supported subset; returns false for unsupported encodings.
- Initial `execute_instruction_step` wrapper advances the 32-bit PC by 4 only when a supported non-control-flow ALU instruction executes; unsupported encodings leave PC unchanged. This is not yet a full EE instruction cycle and does not implement branches or delay slots.
- Unit tests for memory, CPU state, and ALU helper behavior.
- CMake/CTest configuration and a GitHub Actions host-test workflow.

## Verification
- The earlier memory test was compiled and run locally.
- ALU helper, decoder and interpreter test sources cover the current subset, including PC-step success/failure behavior; the full current CMake/CTest suite has not yet been re-run and must not be marked passing.
- No successful remote GitHub Actions run has been confirmed for the latest changes.
- No Xbox 360 Xenon toolchain build has been demonstrated.
- No `Xenon.elf`, `default.xex`, or running Xbox 360 build has been produced or validated.
- The current ALU helpers are isolated 32-bit-lane scaffolding, not a complete R5900 decoder or Emotion Engine implementation. EE-specific 64/128-bit operations, PC/delay-slot execution, exceptions, VU units, Graphics Synthesizer and IOP remain pending.

## Next gates
1. Run the complete CMake build and CTest suite; preserve logs and fix any failures.
2. Run decoder/interpreter tests and the full CMake/CTest suite; fix any failures before expanding instruction coverage.
3. Implement branch/jump decoding and branch-delay-slot state with separate tests; current PC-step support is limited to non-control-flow ALU instructions.
4. Audit source provenance and licenses before selecting an engine strategy.
5. Validate a lawful Xenon/libXenon toolchain in CI.
6. Generate a minimal Xenon ELF only after target compilation is demonstrated; then proceed to XEX.

## Status vocabulary
- Planned: design documented.
- Implemented: source code exists.
- Compiled: build completed successfully and logs are available.
- Tested: tests ran successfully and results are recorded.
- Hardware validated: executed on Xbox 360 RGH with evidence recorded.

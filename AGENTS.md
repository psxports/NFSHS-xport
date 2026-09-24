# Need for Speed: High Stakes

Applies to this project. Resolve `[XPORT_ROOT]` from `xport-project.json` (`toolset` points to its `tools` directory) and read `[XPORT_ROOT]/tools/PIPELINE.md` before work. Shared PSX/MIPS methodology, SQL contracts, status gates and commands live there; keep game-specific facts here.

## Project facts

- Native short name: `NFSHS`; VS2022 v143 Debug x86; solution `src/platform/win/NFSHS.sln`; executable `bin/NFSHS.exe`; working directory `bin`; intermediates `_build`
- The retained reconstruction mixes C and C++ sources. It uses the shared xport process, PsyQ, SPU, window, input, timer and audio runtime; NFSHS-specific adapters live under `src/host`, while `src/platform/win` contains only `NFSHS.sln` and `NFSHS.vcxproj`
- Shared PsyQ code calls the required NFSHS `xport_game_*` services as ordinary link-time externs implemented in `src/host/psx_host.cpp`; callback registration and silent fallbacks are forbidden
- The supplied disc image is present, but its revision and original executable are not yet audited; accepted IDA images, Ghidra PsyQ classification, trace hooks/layout and native continuation ABI are also absent. Do not infer them from filenames or another game
- The supplied CUE contains one `MODE2/2352` data track and no Red Book `AUDIO` tracks; NFSHS music uses XA-ADPCM inside the data track, so `convert_music` must return `not_applicable` and `bin/MUSIC` is not generated
- Trace workflow stays disabled until NFSHS-specific hooks, capture layout, continuation ABI and adapter are evidence-backed and validated end to end
- Reusable tooling belongs in `[XPORT_ROOT]/tools`; the mandatory bidirectional PSX/PsyQ runtime and common `xport.h` types belong in `[XPORT_ROOT]/src`; game code uses the shared `uint8/sint8` through `uint64/sint64` names rather than project copies or `<stdint.h>` names
- NFSHS-specific addresses, reconstructed EAC library code, bindings, diagnostics, tests and evidence remain in this project. Fighting Force is a structural reference only; its game facts and completion claims do not transfer
- Current agreed dummy scope is not established. Preserve existing behavior and do not add new stubs or invented success returns during migration
- Brief comments start with a capital letter and omit the final period

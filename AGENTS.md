# Need for Speed: High Stakes

Resolve `[XPORT_ROOT]` from `xport-project.json` and read `[XPORT_ROOT]/AGENTS.md`.

## Project facts

- Native short name: `NFSHS`; mixed C/C++; VS2022 v143 Debug x86; `src/platform/win/NFSHS.sln` -> `bin/NFSHS.exe`; working directory `bin`; intermediates `_build`
- Compile the shared xport runtime directly; NFSHS adapters stay under `src/host`, and `src/platform/win` contains only build files
- Disc revision, executable identity, IDA images, PsyQ classification, trace hooks/layout and continuation ABI are not yet audited. Do not infer them from filenames or another game
- The reviewed CUE has one `MODE2/2352` data track and no Red Book tracks. `convert_music` must return `not_applicable`; XA-ADPCM remains data-track content
- Trace workflow stays disabled until NFSHS-specific hooks, layout, continuation ABI and adapter pass end-to-end validation
- Agreed dummy scope is not established. Preserve behavior and do not add stubs or invented success returns
- NFSHS addresses, EAC code, bindings, diagnostics and evidence remain project-local; Fighting Force is structural reference only

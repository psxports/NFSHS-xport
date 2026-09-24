# NFSHS-xport
Need for Speed: High Stakes (PSX) decompilation port via Codex

A source-level reconstruction of the PlayStation build of *Need for Speed: High Stakes*
(NFS4, SLUS‑006.20) — translating the original linked `.obj` modules back into faithful,
**self-contained, recompilable C++**.

The original game executable is **not** included (it is copyrighted EA material and is used
only as a debug oracle). This repository contains only reconstructed source.

## Status

Reconstruction of executable code is **complete** — every function whose code exists in the
game binary has been reconstructed and links. Verified by a whole‑tree link harness:

```
838 → 196 unresolved symbols
196 = 99 method-hygiene + 89 cdtor-hygiene + 8 inline/host non-gaps + 0 genuine missing-code gaps
```

The remaining **188 are linkage-hygiene** (function bodies exist as C++ members; some call
sites still reference the flat cfront‑style `extern "C"` names) — being resolved with thin
`extern "C"` trampolines. The **8 inline/host** symbols (`alloca`, GTE `cop2` intrinsics,
`trap`/`break`, `operator delete`, x86 `__chkstk_ms`) are compiler/inline constructs, correct
as-is and never external in a real PsyQ build.

## Layout

```
src/eaclib/         EA cross-platform + PSX library
src/frontend/       Front-end menus and screens
src/game/           Gameplay, physics, cars, HUD and track code
src/lib/            Shared cross-module declarations
src/host/           NFSHS-specific host adapters, diagnostics and link support
src/platform/win/   Visual Studio solution and project only
tools/              Reconstruction and verification tools
tmp/                Historical and temporary reconstruction artifacts
_build/             Compiler and linker intermediate files
bin/                NFSHS.exe and local game data
```

## Windows build

Open `src/platform/win/NFSHS.sln` in Visual Studio 2022 and build the
`Release|Win32` configuration. The executable is written to `bin/NFSHS.exe` and
all intermediate files are written below `_build`.

The native port is built exclusively with the Visual Studio 2022 Win32 toolchain.
The same build can be invoked from the repository root:

```powershell
& "C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe" src/platform/win/NFSHS.sln /m /p:Configuration=Release /p:Platform=Win32
```

The public PsyQ compatibility surface, standard types and Windows backend come from the
shared `../xport/src` runtime. The project defines `WND_TITLE` as
`"Need For Speed: High Stakes (xport)"` in both native configurations.
Shared PsyQ entrypoints call the game's required GPU, sound and lifecycle bindings directly
through the ordinary link-time interface declared by the shared runtime; there is no callback registry.

The shared pipeline build and smoke checks can be run from the repository root:

```powershell
python -B ..\xport\tools\xport.py --project . code_refresh
```

Extracted game data is local-only and is not distributed. Place it in
`bin/DATA` before running the port.

## Methodology

Each `.obj` was reconstructed from a triple-source authority:

- **disasm-v3** — trusted MIPS disassembly (authoritative for code, args, returns).
- **PsyQ SYM (v3)** — symbol/field/local names (PsyQ MND dump).
- **Ghidra C/C++ export** — structural decompilation (cross-checked against disasm; Ghidra
  is known to drop args under "unknown calling convention" and occasionally emit wrong
  constants, so every call's arguments are verified against the disassembly).

Goal / seal criteria: the tree builds from itself with Visual Studio 2022 for Win32, has no
unresolved absolute VAs in code, and every materialized item carries a `/* @0xVA */` breadcrumb.

## Verifying self-containment

The native Visual Studio project directly includes every C and C++ translation unit
under `src/game`, `src/frontend`, and `src/eaclib`, plus the reconstruction and
host translation units listed in `NFSHS.vcxproj`. A clean Debug and Release
build therefore verifies the complete supported source tree without Python or MinGW.

## Credits

Reconstruction is decompilation-to-source; this is **not** original EA source.
Thanks to Ben Lincoln for the *"This Dust Remembers What It Once Was"* tooling that the
original decomp effort was built on.

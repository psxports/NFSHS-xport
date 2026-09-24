/* link_hwreg.cpp -- AGGREGATION TU. PSX hardware-register names referenced as
 * `extern volatile` VARIABLES by the eaclib/sound TUs (vs `#define` MMIO macros in
 * libcd/libspu). Types confirmed via NFS4-clean.c Ghidra export (word=u16, dword=u32)
 * + tree extern decls. Defined here as typed globals so the tree links self-contained.
 * NOTE: faithful PSX build should map these to MMIO 0x1F801xxx (SPU/CD/DMA) -- follow-up. */
extern "C" {
volatile unsigned int  D4_BCR;
volatile unsigned int  D4_CHCR;
volatile unsigned int  D4_MADR;
volatile unsigned int  DPCR;
volatile unsigned int  SPU_DELAY;
}

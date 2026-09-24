/* Minimal observable PSX CRT semantics needed by the native port.
 *
 * The Windows build deliberately uses the host CRT for ordinary strings,
 * memory and formatting.  rand and qsort are exceptions: their algorithms
 * affect game state/order and differ from MSVCRT.  Keep only those two
 * contracts here instead of linking the reconstructed PsyQ libc archive.
 */
#include <stddef.h>

static unsigned int g_psx_bios_rand_seed = 1;

/* PSX BIOS A0:2F/A0:30.  The default seed is one. */
extern "C" int rand(void)
{
    g_psx_bios_rand_seed = g_psx_bios_rand_seed * 0x41c64e6du + 0x3039u;
    return (int)((g_psx_bios_rand_seed >> 16) & 0x7fffu);
}

extern "C" void srand(unsigned int seed)
{
    g_psx_bios_rand_seed = seed;
}

/* Observation-only hook used by the opt-in native replay telemetry. */
extern "C" unsigned int NFSHS_HostPSXRandSeed(void)
{
    return g_psx_bios_rand_seed;
}

static void psx_qsort_swap(unsigned char *left, unsigned char *right, size_t size)
{
    for (size_t i = 0; i < size; ++i) {
        unsigned char value = left[i];
        left[i] = right[i];
        right[i] = value;
    }
}

/* PsyQ libc qsort @0x800E5D8C.  Pivot selection and strict-less-than
 * partitioning are observable when the comparator reports equal keys. */
extern "C" void qsort(void *base, size_t count, size_t size,
                       int (*compare)(const void *, const void *))
{
    unsigned char *bytes = (unsigned char *)base;
    if (count < 2)
        return;
    if (count == 2) {
        if (compare(bytes, bytes + size) > 0)
            psx_qsort_swap(bytes, bytes + size, size);
        return;
    }

    psx_qsort_swap(bytes, bytes + (count >> 1) * size, size);
    unsigned char *boundary = bytes;
    unsigned char *element = bytes + size;
    size_t lower_count = 0;
    for (size_t i = 1; i < count; ++i, element += size) {
        if (compare(element, bytes) < 0) {
            boundary += size;
            ++lower_count;
            if (element != boundary)
                psx_qsort_swap(element, boundary, size);
        }
    }
    if (boundary != bytes)
        psx_qsort_swap(bytes, boundary, size);

    qsort(bytes, lower_count, size, compare);
    qsort(boundary + size, count - lower_count - 1, size, compare);
}

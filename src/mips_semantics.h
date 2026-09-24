#ifndef NFS4_MIPS_SEMANTICS_H
#define NFS4_MIPS_SEMANTICS_H

/* Defined C++ equivalents for the R3000A's 32-bit bit operations.  Keep these
   at reconstruction sites where signed C++ arithmetic would otherwise be
   undefined, while the original instruction has modulo-2^32 semantics. */
static inline int nfs4_mips_bits_to_s32(unsigned int bits)
{
    return bits <= 0x7fffffffU ? (int)bits : -1 - (int)~bits;
}

static inline int nfs4_mips_sll_s32(int value, unsigned int shift)
{
    unsigned int bits = (unsigned int)value << (shift & 31);
    return nfs4_mips_bits_to_s32(bits);
}

static inline int nfs4_mips_sra_s32(int value, unsigned int shift)
{
    unsigned int amount = shift & 31;
    unsigned int bits;

    if (amount == 0)
        return value;
    bits = (unsigned int)value >> amount;
    if ((unsigned int)value & 0x80000000U)
        bits |= ~0U << (32 - amount);
    return nfs4_mips_bits_to_s32(bits);
}

static inline int nfs4_mips_srav_s32(int value, int shift)
{
    return nfs4_mips_sra_s32(value, (unsigned int)shift);
}

static inline int nfs4_mips_addu_s32(int left, int right)
{
    return nfs4_mips_bits_to_s32((unsigned int)left + (unsigned int)right);
}

static inline int nfs4_mips_subu_s32(int left, int right)
{
    return nfs4_mips_bits_to_s32((unsigned int)left - (unsigned int)right);
}

static inline int nfs4_mips_mult_s32(int left, int right)
{
    long long product = (long long)left * (long long)right;
    return nfs4_mips_bits_to_s32((unsigned int)(unsigned long long)product);
}

static inline int nfs4_mips_negu_s32(int value)
{
    return nfs4_mips_bits_to_s32(0U - (unsigned int)value);
}

/* ccpsx emits an explicit BREAK for the two architecturally exceptional
   signed DIV cases before reading LO.  Keep those cases defined on a host
   compiler as well; ordinary quotients truncate toward zero on both MIPS and
   C++. */
static inline int nfs4_mips_div_s32(int dividend, int divisor)
{
    if (divisor == 0 || (dividend == nfs4_mips_bits_to_s32(0x80000000U) && divisor == -1))
    {
#if defined(_MSC_VER)
        __debugbreak();
#else
        abort();
#endif
        return 0;
    }
    return dividend / divisor;
}

/* DIVU leaves the remainder in HI and traps through the compiler-emitted
   BREAK 7 guard when the divisor is zero.  Keep the same defined boundary so
   host optimization cannot assume a decompiled empty zero check is dead. */
static inline unsigned int nfs4_mips_modu_u32(unsigned int dividend, unsigned int divisor)
{
    if (divisor == 0)
    {
#if defined(_MSC_VER)
        __debugbreak();
#else
        abort();
#endif
        return 0;
    }
    return dividend % divisor;
}

static inline int nfs4_mips_sign_extend(unsigned int value, unsigned int bits)
{
    unsigned int sign = 1U << (bits - 1);
    unsigned int mask = (sign << 1) - 1;
    return (int)((value & mask) ^ sign) - (int)sign;
}

static inline void nfs4_mips_copy_bytes(void *destination, const void *source, unsigned int count)
{
    unsigned char *out = (unsigned char *)destination;
    const unsigned char *in = (const unsigned char *)source;
    while (count-- != 0)
        *out++ = *in++;
}

#endif

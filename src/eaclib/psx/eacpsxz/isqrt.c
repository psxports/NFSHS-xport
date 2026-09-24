/* isqrt, original 0x800F32CC..0x800F348C.
 * isqrttbl is stored as packed words by link_init.cpp, but every original
 * access is LBU. Both bounds come from adjacent bytes of this ONE table;
 * DAT_8013be0f names the byte before the table, not a separate array.
 */
extern "C" unsigned short isqrttbl[132];

extern "C" unsigned int isqrt(unsigned int a)
{
    const unsigned char *table = (const unsigned char *)isqrttbl;
    unsigned int lo, hi, mid, index, shift;
    if (a & 0xffff0000u)
    {
        shift = (a & 0xff000000u) ? 8 : 4;
        index = a >> (shift == 8 ? 24 : 16);
        lo = (unsigned int)table[index - 1] << shift;
        hi = ((unsigned int)table[index] + 1) << shift;
        while (hi - lo >= 2)
        {
            mid = (lo + hi) >> 1;
            if (a < mid * mid)
                hi = mid;
            else
                lo = mid;
        }
        return lo;
    }
    if (!(a & 0xff00u))
        return a ? table[a - 1] >> 4 : 0;
    /* 0x800F3384..0x800F342C: one bisection below 65536. */
    if (a & 0xc000u)
    {
        index = a >> 8;
        shift = 0;
    }
    else if (a & 0xf000u)
    {
        index = a >> 6;
        shift = 1;
    }
    else if (a & 0xc00u)
    {
        index = a >> 4;
        shift = 2;
    }
    else
    {
        index = a >> 2;
        shift = 3;
    }
    lo = table[index - 1] >> shift;
    hi = (table[index] >> shift) + 1;
    if (hi - lo < 2)
        return lo;
    mid = (lo + hi) >> 1;
    return a < mid * mid ? lo : mid;
}

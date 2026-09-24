/* frontend/common/unpack.c -- RECONSTRUCTED (NFS4 PSX decompression dispatch; C TU)
 *   4 free fns: unpackz/unpack (decompress), unpacksizez/unpacksize (decompressed-size query).
 *   Reads the 2-byte magic (xxFB) and forwards to the eaclib EACPSXZ codec backends
 *   (unrefpack / unhuff / unbtree / getm). unpack & unpacksize are thin public wrappers.
 */
#include "../../nfs4_types.h"
#include "unpack_externs.h"

/* ---- unpackz  [UNPACK.C:59-101] SLD-VERIFIED ---- */
extern "C" long unpackz(void *src, void *dst)

{
    u_char *bytes;
    long len;
    u_char magic;

    bytes = (u_char *)src;
    if ((bytes[1] != 0xfb) && (bytes[1] != 0x32))
    {
        return 0;
    }
    magic = bytes[0] & 0xfe;
    if (magic != 0x32)
    {
        if (magic < 0x33)
        {
            if (magic == 0x10)
            {
                len = unrefpack(src, dst, 1);
                return len;
            }
            if (magic != 0x30)
            {
                return 0;
            }
        }
        else if (magic != 0x34)
        {
            if (magic != 0x46)
            {
                return 0;
            }
            len = unbtree(src, dst, 0);
            return len;
        }
    }
    len = unhuff(src, dst, 1);
    return len;
}

/* ---- unpack  [UNPACK.C:104-116] SLD-VERIFIED ---- */
extern "C" long unpack(void *src, void *dst)

{
    return unpackz(src, dst);
}

/* ---- unpacksizez  [UNPACK.C:165-193] SLD-VERIFIED ---- */
long unpacksizez(void *src)

{
    u_char *bytes;
    long len;
    u_char magic;

    bytes = (u_char *)src;
    if ((bytes[1] != 0xfb) && (bytes[1] != 0x32))
    {
        return 0;
    }
    magic = bytes[0] & 0xfe;
    if (magic != 0x32)
    {
        if (magic < 0x33)
        {
            if (magic != 0x18)
            {
                if (magic < 0x19)
                {
                    if (magic != 0x10)
                    {
                        return 0;
                    }
                }
                else if (magic != 0x30)
                {
                    return 0;
                }
            }
        }
        else if (magic != 0x46)
        {
            if (magic < 0x47)
            {
                if (magic != 0x34)
                {
                    return 0;
                }
            }
            else if (magic != 0x4a)
            {
                return 0;
            }
        }
    }
    len = getm(bytes + 2, 3);
    return len;
}

/* ---- unpacksize  [UNPACK.C:196-208] SLD-VERIFIED ---- */
extern "C" long unpacksize(void *src)

{
    return unpacksizez(src);
}

/* end of unpack.c */

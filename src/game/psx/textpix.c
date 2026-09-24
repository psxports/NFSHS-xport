/* frontend/common/textpix.c -- RECONSTRUCTED (NFS4 PSX text pixel-width calc; C TU)
 *   2 free fns: textnpixels(str,n) sums glyph advance widths over up to n decoded code-points
 *   (decoder fn-ptr @ currentfont+0xA0 reads+advances the string; getcharacter() -> glyph block,
 *   advance byte at charactertbl+8); textpixels(string) = textnpixels(string, 0x100).
 */
#include "../../nfs4_types.h"
#include "textpix_externs.h"

/* ---- textnpixels  [TEXTPIX.C:61-98] SLD-VERIFIED ---- */
int textnpixels(char *str, int n)

{
    charactertbl *ch;
    int code;
    int stringlen;
    int i;
    int dx;
    unsigned char *cursor;

    i = 0;
    stringlen = 0;
    if (0 < n)
    {
        do
        {
            cursor = (unsigned char *)str;
            code = currentfont.decoder(&cursor);
            str = (char *)cursor;
            i = i + 1;
            if (code == 0)
            {
                return stringlen;
            }
            ch = getcharacter(code);
            if (ch != 0)
            {
                dx = ch->advance;
                stringlen = stringlen + dx;
            }
        } while (i < n);
    }
    return stringlen;
}

/* ---- textpixels  [TEXTPIX.C:101-102] SLD-VERIFIED ---- */
extern "C" int textpixels(char *string)

{
    return textnpixels(string, 0x100);
}

/* end of textpix.c */

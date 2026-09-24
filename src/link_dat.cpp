/* link_dat.cpp -- AGGREGATION TU (Stage 3). Definitions for the DAT_xxxx
 * UNNAMED-data globals (Ghidra-named by VA) that were `extern`-declared but
 * never defined. VA encoded in the name. BSS -> zero-init; in-image -> byte-
 * exact from NFS4.EXE. Types from extern decls. (#75/#183 core.) */
#include "nfs4_types.h"

extern "C" {

unsigned int DAT_801235f8 = 0x883126e9u;                                                   /* @801235f8 seedX[1] CPE e92631882fdd24c6 */
unsigned int DAT_801235fc = 0xc624dd2fu;                                                   /* @801235fc seedX[2] CPE 2fdd24c69cc40207 */
unsigned int DAT_80123600 = 0x0702c49cu;                                                   /* @80123600 seedX[3] CPE 9cc402077d3f359e */
unsigned int DAT_80123604 = 0x9e353f7du;                                                   /* @80123604 seedX[4] CPE 7d3f359e643bdf6f */
unsigned int DAT_80123608 = 0x6fdf3b64u;                                                   /* @80123608 seedX[5] CPE 643bdf6f010c3612 */
int DAT_80134a6c;                                                                          /* @80134a6c 0B IMG */
/* @80135c58 CRC-16 (poly 0xA001 reflected) low-byte table [256], CPE head 00c1814001c08041 */
unsigned char DAT_80135c58[256] = {
    0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,0x01,0xc0,0x80,0x41,0x00,0xc1,0x81,0x40,
    0x01,0xc0,0x80,0x41,0x00,0xc1,0x81,0x40,0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,
    0x01,0xc0,0x80,0x41,0x00,0xc1,0x81,0x40,0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,
    0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,0x01,0xc0,0x80,0x41,0x00,0xc1,0x81,0x40,
    0x01,0xc0,0x80,0x41,0x00,0xc1,0x81,0x40,0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,
    0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,0x01,0xc0,0x80,0x41,0x00,0xc1,0x81,0x40,
    0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,0x01,0xc0,0x80,0x41,0x00,0xc1,0x81,0x40,
    0x01,0xc0,0x80,0x41,0x00,0xc1,0x81,0x40,0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,
    0x01,0xc0,0x80,0x41,0x00,0xc1,0x81,0x40,0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,
    0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,0x01,0xc0,0x80,0x41,0x00,0xc1,0x81,0x40,
    0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,0x01,0xc0,0x80,0x41,0x00,0xc1,0x81,0x40,
    0x01,0xc0,0x80,0x41,0x00,0xc1,0x81,0x40,0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,
    0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,0x01,0xc0,0x80,0x41,0x00,0xc1,0x81,0x40,
    0x01,0xc0,0x80,0x41,0x00,0xc1,0x81,0x40,0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,
    0x01,0xc0,0x80,0x41,0x00,0xc1,0x81,0x40,0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,
    0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,0x01,0xc0,0x80,0x41,0x00,0xc1,0x81,0x40,
};
/* @80135d58 CRC-16 (poly 0xA001 reflected) high-byte table [256], CPE head 00c0c101c30302c2 */
unsigned char DAT_80135d58[256] = {
    0x00,0xc0,0xc1,0x01,0xc3,0x03,0x02,0xc2,0xc6,0x06,0x07,0xc7,0x05,0xc5,0xc4,0x04,
    0xcc,0x0c,0x0d,0xcd,0x0f,0xcf,0xce,0x0e,0x0a,0xca,0xcb,0x0b,0xc9,0x09,0x08,0xc8,
    0xd8,0x18,0x19,0xd9,0x1b,0xdb,0xda,0x1a,0x1e,0xde,0xdf,0x1f,0xdd,0x1d,0x1c,0xdc,
    0x14,0xd4,0xd5,0x15,0xd7,0x17,0x16,0xd6,0xd2,0x12,0x13,0xd3,0x11,0xd1,0xd0,0x10,
    0xf0,0x30,0x31,0xf1,0x33,0xf3,0xf2,0x32,0x36,0xf6,0xf7,0x37,0xf5,0x35,0x34,0xf4,
    0x3c,0xfc,0xfd,0x3d,0xff,0x3f,0x3e,0xfe,0xfa,0x3a,0x3b,0xfb,0x39,0xf9,0xf8,0x38,
    0x28,0xe8,0xe9,0x29,0xeb,0x2b,0x2a,0xea,0xee,0x2e,0x2f,0xef,0x2d,0xed,0xec,0x2c,
    0xe4,0x24,0x25,0xe5,0x27,0xe7,0xe6,0x26,0x22,0xe2,0xe3,0x23,0xe1,0x21,0x20,0xe0,
    0xa0,0x60,0x61,0xa1,0x63,0xa3,0xa2,0x62,0x66,0xa6,0xa7,0x67,0xa5,0x65,0x64,0xa4,
    0x6c,0xac,0xad,0x6d,0xaf,0x6f,0x6e,0xae,0xaa,0x6a,0x6b,0xab,0x69,0xa9,0xa8,0x68,
    0x78,0xb8,0xb9,0x79,0xbb,0x7b,0x7a,0xba,0xbe,0x7e,0x7f,0xbf,0x7d,0xbd,0xbc,0x7c,
    0xb4,0x74,0x75,0xb5,0x77,0xb7,0xb6,0x76,0x72,0xb2,0xb3,0x73,0xb1,0x71,0x70,0xb0,
    0x50,0x90,0x91,0x51,0x93,0x53,0x52,0x92,0x96,0x56,0x57,0x97,0x55,0x95,0x94,0x54,
    0x9c,0x5c,0x5d,0x9d,0x5f,0x9f,0x9e,0x5e,0x5a,0x9a,0x9b,0x5b,0x99,0x59,0x58,0x98,
    0x88,0x48,0x49,0x89,0x4b,0x8b,0x8a,0x4a,0x4e,0x8e,0x8f,0x4f,0x8d,0x4d,0x4c,0x8c,
    0x44,0x84,0x85,0x45,0x87,0x47,0x46,0x86,0x82,0x42,0x43,0x83,0x41,0x81,0x80,0x40,
};
/* DAT_80136cae owned by eaclib/psx/sndpsxz/scdvol.cpp (= 127, @0x80136CAE); stray dup removed (datamat audit) */
unsigned char DAT_80136df0;                                                                /* @80136df0 0B IMG */
/* Retail 0x8013BD50..0x8013BE0F: 96-entry ASCII-to-full-width Shift-JIS
 * table consumed by remapshiftjiscode (index << 1, lhu).  A scalar here made
 * every native lookup except 0x20 run past a distinct C++ object. */
unsigned short DAT_8013bd50[0x60] = {
  0x8140,0x8149,0x8167,0x8194,0x8190,0x8193,0x8195,0x8166,
  0x8169,0x816A,0x8196,0x817B,0x8143,0x817C,0x8144,0x815E,
  0x824F,0x8250,0x8251,0x8252,0x8253,0x8254,0x8255,0x8256,
  0x8257,0x8258,0x8146,0x8147,0x8183,0x8181,0x8184,0x8148,
  0x8197,0x8260,0x8261,0x8262,0x8263,0x8264,0x8265,0x8266,
  0x8267,0x8268,0x8269,0x826A,0x826B,0x826C,0x826D,0x826E,
  0x826F,0x8270,0x8271,0x8272,0x8273,0x8274,0x8275,0x8276,
  0x8277,0x8278,0x8279,0x816D,0x815F,0x816E,0x81AA,0x8151,
  0x8165,0x8281,0x8282,0x8283,0x8284,0x8285,0x8286,0x8287,
  0x8288,0x8289,0x828A,0x828B,0x828C,0x828D,0x828E,0x828F,
  0x8290,0x8291,0x8292,0x8293,0x8294,0x8295,0x8296,0x8297,
  0x8298,0x8299,0x829A,0x816F,0x8162,0x8170,0x8160,0x81A6
};                                                                                         /* @8013bd50 192 bytes from NFS4.EXE */
unsigned char DAT_8013be0f = 0x81;                                                         /* @8013be0f rcossin_tbl+0x40ef CPE 810110be13800001 */
int DAT_8013dd48 = 0x004D4152;                                                             /* @8013dd48 'RAM' tag .sdata CPE 52414d00014cdd13 */
short DAT_80147910;                                                                        /* @80147910 0B BSS */
unsigned short DAT_80147912;                                                               /* @80147912 0B BSS */
#ifndef AP_WIN
unsigned char DAT_80147919;                                                                /* @80147919 0B BSS */
int DAT_8014791c;                                                                          /* @8014791c 0B BSS */
int DAT_80147920;                                                                          /* @80147920 0B BSS */
signed char DAT_80147924;                                                                  /* @80147924 0B BSS */
char DAT_80147925;                                                                         /* @80147925 0B BSS */
char DAT_80147926;                                                                         /* @80147926 0B BSS */
int DAT_80147928;                                                                          /* @80147928 0B BSS */
int DAT_8014792c;                                                                          /* @8014792c 0B BSS */
unsigned short DAT_80147930;                                                               /* @80147930 0B BSS */
unsigned char DAT_80147932;                                                                /* @80147932 0B BSS */
unsigned char DAT_80147934;                                                                /* @80147934 0B BSS */
int DAT_80147938;                                                                          /* @80147938 0B BSS */
unsigned char DAT_801479f0;                                                                /* @801479f0 0B BSS */
unsigned char DAT_801479f4;                                                                /* @801479f4 0B BSS */
int DAT_801479f8;                                                                          /* @801479f8 0B BSS */
unsigned char DAT_801479fc;                                                                /* @801479fc 0B BSS */
unsigned char DAT_80147a00;                                                                /* @80147a00 0B BSS */
unsigned char DAT_80147a04;                                                                /* @80147a04 0B BSS */
unsigned char DAT_80147a08;                                                                /* @80147a08 0B BSS */
unsigned char DAT_80147a0a;                                                                /* @80147a0a 0B BSS */
unsigned char DAT_80147a0c;                                                                /* @80147a0c 0B BSS */
unsigned char DAT_80147a0d;                                                                /* @80147a0d 0B BSS */
unsigned char DAT_80147a0e;                                                                /* @80147a0e 0B BSS */
unsigned char DAT_80147a0f;                                                                /* @80147a0f 0B BSS */
unsigned char DAT_80147a10;                                                                /* @80147a10 0B BSS */
unsigned char DAT_80147a11;                                                                /* @80147a11 0B BSS */
unsigned char DAT_80147a12;                                                                /* @80147a12 0B BSS */
unsigned char DAT_80147a13;                                                                /* @80147a13 0B BSS */
unsigned char DAT_80147a14;                                                                /* @80147a14 0B BSS */
unsigned char DAT_80147a15;                                                                /* @80147a15 0B BSS */
unsigned char DAT_80147a16;                                                                /* @80147a16 0B BSS */
unsigned char DAT_80147a17;                                                                /* @80147a17 0B BSS */
unsigned char DAT_80147a18;                                                                /* @80147a18 0B BSS */
intptr DAT_80147e10;                                                                     /* @80147e10 packet-context pointer word */
unsigned int  * DAT_80147e14;                                                              /* @80147e14 0B BSS */
unsigned int  * DAT_80147e18;                                                              /* @80147e18 0B BSS */
unsigned int  * DAT_80147e1c;                                                              /* @80147e1c 0B BSS */
unsigned int  * DAT_80147e20;                                                              /* @80147e20 0B BSS */
int DAT_80147e24;                                                                          /* @80147e24 0B BSS */
int DAT_80147e28;                                                                          /* @80147e28 0B BSS */
int DAT_80147e2c;                                                                          /* @80147e2c 0B BSS */
unsigned short DAT_80147e38;                                                               /* @80147e38 0B BSS */
#endif
#ifndef AP_WIN
int DAT_80148064;                                                                          /* @80148064 0B BSS */
#endif
#ifndef AP_WIN
int DAT_80148440;                                                                          /* @80148440 0B BSS */
int DAT_80148444;                                                                          /* @80148444 0B BSS */
int DAT_80148448;                                                                          /* @80148448 0B BSS */
int DAT_8014844c;                                                                          /* @8014844c 0B BSS */
#endif
short DAT_801484e8;                                                                        /* @801484e8 0B BSS */
short DAT_801484ea;                                                                        /* @801484ea 0B BSS */
int DAT_801486e8;                                                                          /* @801486e8 0B BSS */
int DAT_801486ec;                                                                          /* @801486ec 0B BSS */
int DAT_801486fc;                                                                          /* @801486fc 0B BSS */
int DAT_80148700;                                                                          /* @80148700 0B BSS */
int DAT_80148704;                                                                          /* @80148704 0B BSS */
int DAT_80148708;                                                                          /* @80148708 0B BSS */
#ifndef AP_WIN
short DAT_80148784;                                                                        /* @80148784 0B BSS */
short DAT_80148786;                                                                        /* @80148786 0B BSS */
int DAT_80148788;                                                                          /* @80148788 0B BSS */
unsigned short DAT_8014878c;                                                               /* @8014878c 0B BSS */
#endif
}

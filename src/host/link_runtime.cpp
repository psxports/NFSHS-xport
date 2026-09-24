/* Host implementations for reconstructed runtime intrinsics and data globals */

/* GTE ops are declared in drawc_externs.h WITHOUT extern "C" => C++ linkage
 * (gte_rtps__Fv / gte_lwc2__Fii / gte_swc2__FiPv). Define them as C++ to match. */
#include <string.h>
#include <stdlib.h>
#include "xport.h"
#include "../mips_semantics.h"
#if defined(_MSC_VER)
#include <intrin.h>
#endif
/* Host-side state corresponding to the PSX low-memory and GTE registers */
static unsigned int nfs4_gte_data[32];
struct nfs4_host_matrix { short m[3][3]; short pad; int t[3]; };
static nfs4_host_matrix nfs4_gte_rot;
static int nfs4_gte_trans[3];
static int nfs4_gte_h = 190;
static int nfs4_gte_ofx = 160;
static int nfs4_gte_ofy = 120;
static int nfs4_gte_dqa = -0x1062;
static int nfs4_gte_dqb = 0x1400000;
static int nfs4_gte_far[3];
static unsigned int nfs4_gte_flag;
static void nfs4_gte_finish_flag(void) {
    if(nfs4_gte_flag&0x7f87e000u)nfs4_gte_flag|=0x80000000u;
    nfs4_gte_data[31]=nfs4_gte_flag;
}
static int nfs4_gte_clamp_ir(long long value, unsigned int flag) {
    if (value < -32768) { nfs4_gte_flag |= flag; return -32768; }
    if (value > 32767) { nfs4_gte_flag |= flag; return 32767; }
    return (int)value;
}
void nfs4_gte_set_rot_matrix(const void *ptr) {
    if (ptr) memcpy(&nfs4_gte_rot,ptr,sizeof(nfs4_gte_rot));
}
void nfs4_gte_set_trans_matrix(const void *ptr) {
    if (ptr) memcpy(nfs4_gte_trans,(const char *)ptr+20,sizeof(nfs4_gte_trans));
}
void nfs4_gte_set_trans_vector(const void *ptr) {
    if (ptr) memcpy(nfs4_gte_trans,ptr,sizeof(nfs4_gte_trans));
}
void nfs4_gte_set_trans_xyz(int x,int y,int z) {
    nfs4_gte_trans[0]=x; nfs4_gte_trans[1]=y; nfs4_gte_trans[2]=z;
}
void nfs4_gte_load_ir_short(const void *ptr) {
    if (!ptr) return;
    const short *v=(const short *)ptr;
    /* PsyQ gte_ldsv is used here for a MATRIX column.  The emitted MIPS
       loads halfwords at byte offsets 0, 6 and 12 (for example
       Flare_Halo2 0x800CDCB8..0x800CDCCC), not three adjacent shorts. */
    nfs4_gte_data[9]=(unsigned int)(int)v[0];
    nfs4_gte_data[10]=(unsigned int)(int)v[3];
    nfs4_gte_data[11]=(unsigned int)(int)v[6];
}
void nfs4_gte_store_ir_short(void *ptr) {
    if (!ptr) return;
    short *v=(short *)ptr;
    /* Matching MIPS stores target the same 0/6/12-byte column layout. */
    v[0]=(short)nfs4_gte_data[9]; v[3]=(short)nfs4_gte_data[10]; v[6]=(short)nfs4_gte_data[11];
}
void nfs4_gte_rtir(void) {
    int x=(short)nfs4_gte_data[9],y=(short)nfs4_gte_data[10],z=(short)nfs4_gte_data[11];
    long long tx=((long long)nfs4_gte_rot.m[0][0]*x+(long long)nfs4_gte_rot.m[0][1]*y+(long long)nfs4_gte_rot.m[0][2]*z)>>12;
    long long ty=((long long)nfs4_gte_rot.m[1][0]*x+(long long)nfs4_gte_rot.m[1][1]*y+(long long)nfs4_gte_rot.m[1][2]*z)>>12;
    long long tz=((long long)nfs4_gte_rot.m[2][0]*x+(long long)nfs4_gte_rot.m[2][1]*y+(long long)nfs4_gte_rot.m[2][2]*z)>>12;
    nfs4_gte_flag=0;
    nfs4_gte_data[25]=(unsigned int)tx; nfs4_gte_data[26]=(unsigned int)ty; nfs4_gte_data[27]=(unsigned int)tz;
    nfs4_gte_data[9]=(unsigned int)nfs4_gte_clamp_ir(tx,1u<<24);
    nfs4_gte_data[10]=(unsigned int)nfs4_gte_clamp_ir(ty,1u<<23);
    nfs4_gte_data[11]=(unsigned int)nfs4_gte_clamp_ir(tz,1u<<22);
    nfs4_gte_finish_flag();
}
extern "C" void NFSHS_GTE_SetRotMatrix(const void *ptr) { nfs4_gte_set_rot_matrix(ptr); }
extern "C" void NFSHS_GTE_SetTransMatrix(const void *ptr) { nfs4_gte_set_trans_matrix(ptr); }
extern "C" void NFSHS_GTE_LoadV0(const void *ptr) {
    if (!ptr) return;
    const short *v=(const short *)ptr;
    nfs4_gte_data[0]=(unsigned short)v[0]|((unsigned int)(unsigned short)v[1]<<16);
    nfs4_gte_data[1]=(unsigned short)v[2];
}
extern "C" void NFSHS_GTE_StoreLVNL(void *ptr) {
    if (ptr) memcpy(ptr,&nfs4_gte_data[25],12);
}
extern "C" void NFSHS_GTE_SetGeomScreen(int h) { if (h > 0) nfs4_gte_h=h; }
extern "C" void NFSHS_GTE_SetGeomOffset(int x,int y) { nfs4_gte_ofx=x; nfs4_gte_ofy=y; }
extern "C" void NFSHS_GTE_WriteControl(int reg,int value) {
    /* The native renderer keeps H in integer units and OFX/OFY in pixels;
       retail TrsProj_SetMenuProjection writes control registers 26,24,25
       as H and signed 16.16 offsets respectively. */
    if(reg==26) nfs4_gte_h=value;
    else if(reg==24) nfs4_gte_ofx=value/65536;
    else if(reg==25) nfs4_gte_ofy=value/65536;
    else if(reg==27) nfs4_gte_dqa=(short)value;
    else if(reg==28) nfs4_gte_dqb=value;
}
extern "C" void NFSHS_GTE_SetFarColor(int r,int g,int b) {
    nfs4_gte_far[0]=r<<4; nfs4_gte_far[1]=g<<4; nfs4_gte_far[2]=b<<4;
}
extern "C" void NFSHS_GTE_DebugState(int *h,int *ofx,int *ofy) {
    if(h)*h=nfs4_gte_h; if(ofx)*ofx=nfs4_gte_ofx; if(ofy)*ofy=nfs4_gte_ofy;
}
extern "C" void NFSHS_GTE_DebugTransform(void *matrix,void *translation) {
    if (matrix) memcpy(matrix,&nfs4_gte_rot,20);
    if (translation) memcpy(translation,nfs4_gte_trans,12);
}
static int nfs4_gte_clamp_sxy(long long value, unsigned int flag) {
    if (value < -1024) { nfs4_gte_flag |= flag; return -1024; }
    if (value > 1023) { nfs4_gte_flag |= flag; return 1023; }
    return (int)value;
}
static unsigned int nfs4_gte_clamp_sz(long long value) {
    if (value < 0) { nfs4_gte_flag |= 1u<<18; return 0; }
    if (value > 65535) { nfs4_gte_flag |= 1u<<18; return 65535; }
    return (unsigned int)value;
}
/* The GTE does not use mathematical integer division for RTP.  RTPS/RTPT use
   the hardware UNR reciprocal table followed by two refinement steps.  This
   integer form is the documented table generator and bit-exact algorithm used
   by PSX emulators; exact division differs by one pixel on real NFS4 horizon
   vertices (RTPS at 0x800D1488/0x800D14D0). */
static unsigned int nfs4_gte_unr_divide(unsigned int numerator,unsigned int denominator) {
    if (denominator*2u<=numerator) {
        nfs4_gte_flag|=(1u<<17);
        return 0x1ffffu;
    }
    unsigned int shift=0,scan=denominator&0xffffu;
    while(shift<16 && !(scan&0x8000u)) { scan<<=1; ++shift; }
    unsigned int lhs=numerator<<shift;
    unsigned int rhs=(denominator<<shift)|0x8000u;
    unsigned int index=(((rhs&0x7fffu)+0x40u)>>7);
    int tableValue=((0x40000/(int)(index+0x100u)+1)/2)-0x101;
    if(tableValue<0)tableValue=0;
    int x=0x101+tableValue;
    int d=(-(int)(rhs*x)+0x80)>>8;
    unsigned int reciprocal=(unsigned int)((x*(0x20000+d)+0x80)>>8);
    unsigned int result=(unsigned int)(((unsigned long long)lhs*reciprocal+0x8000u)>>16);
    return result>0x1ffffu?0x1ffffu:result;
}
static void nfs4_gte_project(int x,int y,int z,int last) {
    long long tx=(((long long)nfs4_gte_rot.m[0][0]*x+(long long)nfs4_gte_rot.m[0][1]*y+(long long)nfs4_gte_rot.m[0][2]*z)>>12)+nfs4_gte_trans[0];
    long long ty=(((long long)nfs4_gte_rot.m[1][0]*x+(long long)nfs4_gte_rot.m[1][1]*y+(long long)nfs4_gte_rot.m[1][2]*z)>>12)+nfs4_gte_trans[1];
    long long tz=(((long long)nfs4_gte_rot.m[2][0]*x+(long long)nfs4_gte_rot.m[2][1]*y+(long long)nfs4_gte_rot.m[2][2]*z)>>12)+nfs4_gte_trans[2];
    /* RTPS perspective projection consumes the saturated IR1/IR2 values, not
       the full MAC1/MAC2 intermediates.  Using tx/ty directly made near world
       facets explode to the SXY +/-1024 limits on the native port. */
    int irx=nfs4_gte_clamp_ir(tx,1u<<24);
    int iry=nfs4_gte_clamp_ir(ty,1u<<23);
    int irz=nfs4_gte_clamp_ir(tz,1u<<22);
    unsigned int depth=nfs4_gte_clamp_sz(tz);
    unsigned int quotient=nfs4_gte_unr_divide((unsigned int)nfs4_gte_h,depth);
    long long sx=(long long)nfs4_gte_ofx+(((long long)irx*quotient)>>16);
    long long sy=(long long)nfs4_gte_ofy+(((long long)iry*quotient)>>16);
    nfs4_gte_data[12]=nfs4_gte_data[13]; nfs4_gte_data[13]=nfs4_gte_data[14];
    nfs4_gte_data[14]=(unsigned short)nfs4_gte_clamp_sxy(sx,1u<<14)|((unsigned int)(unsigned short)nfs4_gte_clamp_sxy(sy,1u<<13)<<16);
    nfs4_gte_data[16]=nfs4_gte_data[17]; nfs4_gte_data[17]=nfs4_gte_data[18]; nfs4_gte_data[18]=nfs4_gte_data[19];
    nfs4_gte_data[19]=depth;
    nfs4_gte_data[9]=(unsigned int)irx; nfs4_gte_data[10]=(unsigned int)iry; nfs4_gte_data[11]=(unsigned int)irz;
    nfs4_gte_data[25]=(unsigned int)tx; nfs4_gte_data[26]=(unsigned int)ty; nfs4_gte_data[27]=(unsigned int)tz;
    if(last) {
        long long mac0=(long long)(int)quotient*nfs4_gte_dqa+nfs4_gte_dqb;
        int ir0=(int)(mac0>>12);
        nfs4_gte_data[24]=(unsigned int)mac0;
        if(ir0<0) { ir0=0; nfs4_gte_flag|=1u<<12; }
        else if(ir0>4096) { ir0=4096; nfs4_gte_flag|=1u<<12; }
        nfs4_gte_data[8]=(unsigned int)ir0;
    }
}
void gte_rtps(void) {
    nfs4_gte_flag=0;
    nfs4_gte_project((short)(nfs4_gte_data[0]&0xffff),(short)(nfs4_gte_data[0]>>16),(short)nfs4_gte_data[1],1);
    nfs4_gte_finish_flag();
}
void gte_rtpt(void) {
    nfs4_gte_flag=0;
    for(int i=0;i<3;i++) nfs4_gte_project((short)nfs4_gte_data[i*2],(short)(nfs4_gte_data[i*2]>>16),(short)nfs4_gte_data[i*2+1],i==2);
    nfs4_gte_finish_flag();
}
void nfs4_gte_nclip(void) {
    int x0=(short)nfs4_gte_data[12],y0=(short)(nfs4_gte_data[12]>>16);
    int x1=(short)nfs4_gte_data[13],y1=(short)(nfs4_gte_data[13]>>16);
    int x2=(short)nfs4_gte_data[14],y2=(short)(nfs4_gte_data[14]>>16);
    long long area=(long long)x0*y1+x1*y2+x2*y0-x0*y2-x1*y0-x2*y1;
    nfs4_gte_data[24]=(unsigned int)area;
}
void nfs4_gte_avsz4(void) {
    /* InitGeom writes ZSF4=0x100.  AVSZ4 is not an arithmetic average:
       MAC0=(SZ0+SZ1+SZ2+SZ3)*ZSF4, OTZ=saturate(MAC0>>12). */
    unsigned long long sum=(unsigned long long)(nfs4_gte_data[16]&0xffffu)+
        (nfs4_gte_data[17]&0xffffu)+(nfs4_gte_data[18]&0xffffu)+
        (nfs4_gte_data[19]&0xffffu);
    long long mac0=(long long)(sum*0x100u);
    nfs4_gte_data[24]=(unsigned int)mac0;
    long long otz=mac0>>12;
    nfs4_gte_flag=0;
    if(otz<0) { otz=0; nfs4_gte_flag|=1u<<18; }
    else if(otz>65535) { otz=65535; nfs4_gte_flag|=1u<<18; }
    nfs4_gte_data[7]=(unsigned int)otz;
    nfs4_gte_finish_flag();
}
void nfs4_gte_avsz3(void) {
    /* InitGeom installs ZSF3=0x155 (4096/3 rounded down). */
    unsigned long long sum=(unsigned long long)(nfs4_gte_data[17]&0xffffu)+
        (nfs4_gte_data[18]&0xffffu)+(nfs4_gte_data[19]&0xffffu);
    long long mac0=(long long)(sum*0x155u);
    nfs4_gte_data[24]=(unsigned int)mac0;
    long long otz=mac0>>12;
    nfs4_gte_flag=0;
    if(otz<0) { otz=0; nfs4_gte_flag|=1u<<18; }
    else if(otz>65535) { otz=65535; nfs4_gte_flag|=1u<<18; }
    nfs4_gte_data[7]=(unsigned int)otz;
    nfs4_gte_finish_flag();
}
void nfs4_gte_ldsxy3(int sxy0,int sxy1,int sxy2) {
    nfs4_gte_data[12]=(unsigned int)sxy0; nfs4_gte_data[13]=(unsigned int)sxy1; nfs4_gte_data[14]=(unsigned int)sxy2;
}
void nfs4_gte_stflg(void *ptr) { if(ptr) memcpy(ptr,&nfs4_gte_data[31],4); }
void nfs4_gte_ldir0(int value) {
    if(value<0)value=0; else if(value>4095)value=4095;
    nfs4_gte_data[8]=(unsigned int)value;
}
void nfs4_gte_rt(void) {
    nfs4_gte_flag=0;
    int x=(short)nfs4_gte_data[0], y=(short)(nfs4_gte_data[0]>>16), z=(short)nfs4_gte_data[1];
    long long tx=(((long long)nfs4_gte_rot.m[0][0]*x+(long long)nfs4_gte_rot.m[0][1]*y+(long long)nfs4_gte_rot.m[0][2]*z)>>12)+nfs4_gte_trans[0];
    long long ty=(((long long)nfs4_gte_rot.m[1][0]*x+(long long)nfs4_gte_rot.m[1][1]*y+(long long)nfs4_gte_rot.m[1][2]*z)>>12)+nfs4_gte_trans[1];
    long long tz=(((long long)nfs4_gte_rot.m[2][0]*x+(long long)nfs4_gte_rot.m[2][1]*y+(long long)nfs4_gte_rot.m[2][2]*z)>>12)+nfs4_gte_trans[2];
    nfs4_gte_data[25]=(unsigned int)tx; nfs4_gte_data[26]=(unsigned int)ty; nfs4_gte_data[27]=(unsigned int)tz;
    nfs4_gte_data[9]=(unsigned int)nfs4_gte_clamp_ir(tx,1u<<24);
    nfs4_gte_data[10]=(unsigned int)nfs4_gte_clamp_ir(ty,1u<<23);
    nfs4_gte_data[11]=(unsigned int)nfs4_gte_clamp_ir(tz,1u<<22);
    nfs4_gte_finish_flag();
}
extern "C" void NFSHS_GTE_MVMVA(void) { nfs4_gte_rt(); }
static unsigned int nfs4_gte_depth_color(unsigned int color) {
    int ir0=(int)nfs4_gte_data[8];
    int c[3]={(int)(color&255),(int)((color>>8)&255),(int)((color>>16)&255)};
    for(int i=0;i<3;i++) {
        int base=(int)((unsigned int)c[i]<<4), delta=nfs4_gte_clamp_ir((long long)nfs4_gte_far[i]-base,1u<<(24-i));
        int value=base+((ir0*delta)>>12); c[i]=value<0?0:(value>4080?255:(value>>4));
        nfs4_gte_data[9+i]=(unsigned int)nfs4_gte_clamp_ir(value,1u<<(24-i));
        nfs4_gte_data[25+i]=(unsigned int)value;
    }
    return (color&0xff000000u)|(unsigned int)c[0]|((unsigned int)c[1]<<8)|((unsigned int)c[2]<<16);
}
void nfs4_gte_dpcs(void) {
    nfs4_gte_data[20]=nfs4_gte_data[21]; nfs4_gte_data[21]=nfs4_gte_data[22];
    nfs4_gte_data[22]=nfs4_gte_depth_color(nfs4_gte_data[6]); nfs4_gte_finish_flag();
}
void nfs4_gte_dpct(void) {
    unsigned int in[3]={nfs4_gte_data[20],nfs4_gte_data[21],nfs4_gte_data[22]};
    /* DPCT takes RGB from RGB0..2, but the command/code byte of every output
       comes from RGBC (data register 6).  Keeping each input RGB FIFO entry's
       old high byte diverged from the PSX GTE and from OpenArmstrong's
       gte_DPCT implementation. */
    unsigned int code=nfs4_gte_data[6]&0xff000000u;
    for(int i=0;i<3;i++)
        nfs4_gte_data[20+i]=(nfs4_gte_depth_color(in[i])&0x00ffffffu)|code;
    nfs4_gte_finish_flag();
}
void gte_lwc2(int reg, int data) {
    if ((unsigned int)reg < 32U) nfs4_gte_data[reg] = (unsigned int)data;
}
void gte_swc2(int reg, void *ptr) {
    if ((unsigned int)reg < 32U && ptr != 0) memcpy(ptr, &nfs4_gte_data[reg], 4);
}
extern "C" int NFSHS_GTE_VectorNormal(const void *input,void *output) {
    /* VectorNormal worker 0x800F1B3C..0x800F1BF8: SQR(sf=0),
       LZCS/LZCR, LH from 0x8013485C, GPF(sf=0), then SRAV.
       This is the SDK's quantized normal, not floating-point unit length.
       The return value is the sum of squares (v0), NOT sqrt(sum). */
    static const short reciprocal[192]={
        4096,4064,4033,4003,3973,3944,3916,3888,3861,3835,3809,3783,3758,3734,3710,3686,
        3663,3640,3618,3596,3575,3554,3533,3513,3493,3473,3454,3435,3416,3397,3379,3361,
        3344,3327,3310,3293,3276,3260,3244,3228,3213,3197,3182,3167,3153,3138,3124,3110,
        3096,3082,3069,3055,3042,3029,3016,3003,2991,2978,2966,2954,2942,2930,2919,2907,
        2896,2885,2873,2862,2852,2841,2830,2820,2809,2799,2789,2779,2769,2759,2749,2740,
        2730,2721,2711,2702,2693,2684,2675,2666,2657,2649,2640,2631,2623,2615,2606,2598,
        2590,2582,2574,2566,2558,2550,2543,2535,2528,2520,2513,2505,2498,2491,2484,2477,
        2469,2462,2456,2449,2442,2435,2428,2422,2415,2409,2402,2396,2389,2383,2377,2371,
        2364,2358,2352,2346,2340,2334,2328,2322,2317,2311,2305,2299,2294,2288,2283,2277,
        2272,2266,2261,2255,2250,2245,2239,2234,2229,2224,2219,2214,2209,2204,2199,2194,
        2189,2184,2179,2174,2170,2165,2160,2155,2151,2146,2142,2137,2133,2128,2124,2119,
        2115,2110,2106,2102,2097,2093,2089,2084,2080,2076,2072,2068,2064,2060,2056,2052
    };
    int in[3],out[3],v[3];memcpy(in,input,12);
    unsigned int magnitude=0;
    for(int i=0;i<3;i++) {v[i]=(short)in[i];magnitude+=(unsigned int)(v[i]*v[i]);}
    /* The original uses trapping ADD at 0x800F1B5C/60. */
    if(magnitude>0x7fffffffu)abort();
    unsigned int bits=magnitude;int lz=0;
    if(!bits)lz=32;else while(!(bits&0x80000000u)){++lz;bits<<=1;}
    nfs4_gte_data[30]=magnitude;
    // LZCR is read-only GTE data register 31; this runtime stores FLAG there.
    int even=lz&~1,shift=nfs4_mips_sra_s32(31-even,1);
    unsigned int mantissa=even>=24?magnitude<<(even-24):magnitude>>(24-even);
    // Zero reads LH at table-0x80 (0x801347DC = 6), then multiplies zero.
    int factor=magnitude?reciprocal[mantissa-64]:6;
    nfs4_gte_data[8]=(unsigned int)factor;nfs4_gte_flag=0;
    unsigned int rgb=nfs4_gte_data[6]&0xff000000u;
    for(int i=0;i<3;i++) {
        int product=v[i]*factor;
        nfs4_gte_data[25+i]=(unsigned int)product;
        nfs4_gte_data[9+i]=(unsigned int)nfs4_gte_clamp_ir(product,1u<<(24-i));
        int channel=nfs4_mips_sra_s32(product,4);
        if(channel<0){channel=0;nfs4_gte_flag|=1u<<(21-i);}
        else if(channel>255){channel=255;nfs4_gte_flag|=1u<<(21-i);}
        rgb|=(unsigned int)channel<<(8*i);
        out[i]=nfs4_mips_sra_s32(product,shift);
    }
    nfs4_gte_data[20]=nfs4_gte_data[21];nfs4_gte_data[21]=nfs4_gte_data[22];nfs4_gte_data[22]=rgb;
    nfs4_gte_finish_flag();memcpy(output,out,12);return (int)magnitude;
}

extern "C" {
void _bzero_w(int *p, int n){ while (n-- > 0) *p++ = 0; }  /* static-in-INTR.cpp; cross-TU refs */
unsigned fixedinverse(int x);
#ifndef AP_WIN
unsigned rinverse(int x){ return fixedinverse(x); }   /* alias attr ignored; forward */
#endif
void trap(unsigned int code)
{
    (void)code;
#if defined(_MSC_VER)
    __debugbreak();
#else
    __builtin_trap();
#endif
}
/* PAD_state is provided by the native pad implementation */
short _rsqrt_tbl[256];   /* GTE inverse-sqrt table (BSS, filled at GTE init; idx<0xC0) */
} /* extern "C" */

/* tScreen::fSuppressLoadingText single global (was per-TU `static int` in a header). */
int _7tScreen_fSuppressLoadingText;

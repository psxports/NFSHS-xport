/* SimpleMem allocation methods */
#include "../../nfs4_types.h"
#include "../../lib/libfns.h"

/* ---- Alloc  [SIMPLEMEM.CPP:10-40] SLD-VERIFIED ---- */
void * SimpleMem::Alloc(int len,int feign)
{
  u_int uVar1;
  void *ret;
  
  uVar1 = len + 3U & 0xfffffffc;
  if ((int)uVar1 <= this->freeMemSize) {
    ret = this->freeMem;
    if (feign == 0) {
      this->freeMem = (u_char *)ret + uVar1;
      this->freeMemSize = this->freeMemSize - uVar1;
    }
    return ret;
  }
  return (void *)0x0;
}

/* ---- FeignAlloc  [SIMPLEMEM.CPP:45-46] SLD-VERIFIED ---- */
void * SimpleMem::FeignAlloc(int len)
{
  void *pvVar1;
  
  pvVar1 = (this)->Alloc(len,1);
  return pvVar1;
}

/* ---- ResizeToFit  [SIMPLEMEM.CPP:57-64] SLD-VERIFIED ---- */
void SimpleMem::ResizeToFit()
{
  void *tp1;
  
  tp1 = this->freeMem;
  this->freeMem = (u_char *)0x0;
  resizememadr(this->heap,(int)((u_char *)tp1 - (u_char *)this->heap));
  return;
}

/* end of simplemem.cpp */

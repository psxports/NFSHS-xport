/* SerializedGroup resource container methods */
#include "../../nfs4_types.h"
#include "../../lib/libfns.h"

/* ---- LocateNextGroupType__15SerializedGroupi  [GROUP.CPP:44-58] SLD-VERIFIED ---- */
SerializedGroup * SerializedGroup::LocateNextGroupType(int type)
{
  SerializedGroup *group;

  group = (SerializedGroup *)((u_char *)this + this->m_length);
  if (group->m_type == type) {
    return group;
  }
  return (SerializedGroup *)0x0;
}

/* ---- LocateGroupType__15SerializedGroupii  [GROUP.CPP:63-99] SLD-VERIFIED ---- */
SerializedGroup * SerializedGroup::LocateGroupType(int type,int index)
{
  SerializedGroup *group;
  bool bVar1;
  u_int uVar2;
  int iVar4;
  int iVar5;
  
  iVar5 = 0;
  iVar4 = this->m_num_elements;
  group = this + 1;
  while( true ) {
    iVar4 = iVar4 + -1;
    if (iVar4 == -1) {
      return (SerializedGroup *)0x0;
    }
    if ((group->m_type == type) && (bVar1 = iVar5 == index, iVar5 = iVar5 + 1, bVar1)) break;
    uVar2 = group->m_length & 3;
    if (uVar2 != 0) {
      group->m_length = (group->m_length + 4U) - uVar2;
    }
    group = (SerializedGroup *)((u_char *)group + group->m_length);
  }
  return group;
}

/* ---- LocateGroupNum__15SerializedGroupi  [GROUP.CPP:103-116] SLD-VERIFIED ---- */
SerializedGroup * SerializedGroup::LocateGroupNum(int index)
{
  SerializedGroup *group;
  int iVar1;

  group = this + 1;
  if (this->m_num_elements <= index) {
    return (SerializedGroup *)0;
  }
  iVar1 = 0;
  if (0 < index) {
    do {
      iVar1 = iVar1 + 1;
      group = (SerializedGroup *)((u_char *)group + group->m_length);
    } while (iVar1 < index);
  }
  return group;
}

/* ---- LocateCreateGroupType__15SerializedGroupiP9SimpleMemi  [GROUP.CPP:120-134] SLD-VERIFIED ---- */
void * SerializedGroup::LocateCreateGroupType(int type,SimpleMem *mem_,int index)
{
  SerializedGroup *source;

  source = (this)->LocateGroupType(type,index);
  if (source == (SerializedGroup *)0x0) {
    return (void *)0x0;
  }
  /* PsyQ calls LocateGroupType a second time before CreateLiteGroup. */
  source = (this)->LocateGroupType(type,index);
  return (this)->CreateLiteGroup(source,mem_);
}

/* ---- CreateLiteGroup__15SerializedGroupP15SerializedGroupP9SimpleMem  [GROUP.CPP:168-181] SLD-VERIFIED ---- */
Group * SerializedGroup::CreateLiteGroup(SerializedGroup *source_,SimpleMem *mem_)
{
  u_int *puVar1;
  int n;

  n = source_->m_length + -0xc;
  puVar1 = (u_int *)(mem_)->Alloc(n,0);
  *puVar1 = source_->m_num_elements;
  /* Original 0x8009C2BC-0x8009C2C4 passes n unchanged to blockmove. */
  blockmove((void *)(source_ + 1),puVar1 + 1,n);
  return (Group *)puVar1;
}

/* ---- CreateLiteGroupDataSize__15SerializedGroupP15SerializedGroupP9SimpleMemi  [GROUP.CPP:186-199] SLD-VERIFIED ---- */
Group * SerializedGroup::CreateLiteGroupDataSize(SerializedGroup *source_,SimpleMem *mem_,int dataSize)
{
  u_int *puVar1;

  puVar1 = (u_int *)(mem_)->Alloc(dataSize + 4,0);
  *puVar1 = 0;
  /* Original keeps dataSize+4 in s1 and passes that same value as a2. */
  blockmove((void *)(source_ + 1),puVar1 + 1,dataSize + 4);
  return (Group *)puVar1;
}

/* end of group.cpp */

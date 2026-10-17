#ifndef NFSHS_SPCH_CALLBACKS_H
#define NFSHS_SPCH_CALLBACKS_H

#include "psx.h"

typedef void *(*NFSHS_SpeechAllocator)(int numBytes, char *message);
typedef void (*NFSHS_SpeechFree)(void *memory);
typedef void (*NFSHS_SpeechSampleRequest)(sint32 bank, sint32 offset, sint32 size, sint32 event);
typedef void (*NFSHS_SpeechRuleSet)(sint32 sentence, sint32 rule, sint32 value);
typedef sint32 (*NFSHS_SpeechRuleTest)(sint32 sentence, sint32 rule, sint32 value);

extern "C" {
extern NFSHS_SpeechAllocator gMemAlloc;
extern NFSHS_SpeechFree gMemFree;
extern NFSHS_SpeechSampleRequest gSampleRequest;
extern NFSHS_SpeechRuleSet gSentenceRuleSet;
extern NFSHS_SpeechRuleTest gSentenceRuleTest;
int SPCH_Init(NFSHS_SpeechSampleRequest sampleRequestCb, unsigned int gameNum, int dataRate);
intptr SPCH_InitBankMem(NFSHS_SpeechAllocator memAllocFn, NFSHS_SpeechFree memFreeFn, int numBanks);
}

#endif

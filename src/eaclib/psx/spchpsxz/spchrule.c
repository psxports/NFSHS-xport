/* eaclib/psx/spchpsxz/spchrule.c -- RECONSTRUCTED from nfs4-f.exe. NOT original source.  *** 9/9 ***
 *   Source obj : nfs4\eaclib\psx\spchrule.obj ; archive C:\nfs4\EACLIB\PSX\SPCHPSXZ.LIB (xlsx col12 / SYM v3)
 *   9 fns @[0x8010B100 .. 0x8010B58C].  Sentence rule evaluation -- walk a sentence's rule list, test/apply
 *   parameter rules via the gSentenceRuleTest/gSentenceRuleSet callbacks.  Ghidra nfs4-f.exe.c (spchrule) +
 *   disasm-v3 + IDA sigs.
 *
 *   Linkage: VoxSentence_GetNumPhrases / iSPCH_GetOffset8 / iSPCH_GetOffset16 are per-TU `static` copies of
 *   the shared-header helpers (the canonical versions live in spchdata.obj).
 *   Ghidra-isms resolved: iSPCH_GetRuleSettings' args were dropped (in_a0/a1/a2 -> sentence,values,out per
 *   IDA); iSPCH_SentenceUsesParm reads in_v0 = VoxSentence_GetNumPhrases' dropped return.
 */

#include "../../../nfs4_types.h"

extern "C" intptr gSentenceRuleSet;  /* sentence rule-set callback */
extern "C" intptr gSentenceRuleTest; /* sentence rule-test callback */

/* ---- per-TU static copies of the shared Vox accessors (canonical versions in spchdata.obj) ---- */
static int VoxSentence_GetNumPhrases(intptr sentence) /* @0x8010B100 */
{
    return (int)((unsigned int)*(unsigned char *)(sentence + 3) >> 2);
}

static intptr iSPCH_GetOffset8(intptr base, intptr tableBase, int index) /* @0x8010B10C */
{
    return base + ((int)*(unsigned char *)(tableBase + index) << 2);
}

static intptr iSPCH_GetOffset16(intptr base, intptr tableBase, int index) /* @0x8010B124 */
{
    return base + ((int)*(unsigned short *)(tableBase + index * 2) << 2);
}

extern "C" intptr iSPCH_GetRuleDataAddr(intptr sentence);                                     /* @0x8010B140 */
extern "C" int iSPCH_SentenceUsesParm(intptr sentence, unsigned int paramIdx);                /* @0x8010B158 */
extern "C" unsigned int iSPCH_GetRuleID(intptr sentence, int index);                          /* @0x8010B220 */
extern "C" void iSPCH_RuleSet(short *sentence, int rule, int *values);                        /* @0x8010B294 */
extern "C" unsigned int iSPCH_GetRuleSettings(short *sentence, int *values, char *out);       /* @0x8010B3CC */
extern "C" unsigned int iSPCH_CheckSentenceRules(int testVal, int clearMask, intptr rulePtr); /* @0x8010B58C */

/* iSPCH_GetRuleDataAddr @0x8010B140 : address of a sentence's rule-data block (after its phrase table). */
extern "C" intptr iSPCH_GetRuleDataAddr(intptr sentence)
{
    return sentence + (int)(unsigned int)*(unsigned char *)(sentence + 6) * 2 + 0xc;
}

/* iSPCH_SentenceUsesParm @0x8010B158 : 1 if any phrase of `sentence` references parameter `paramIdx`. */
extern "C" int iSPCH_SentenceUsesParm(intptr sentence, unsigned int paramIdx)
{
    int numPhrases = VoxSentence_GetNumPhrases(sentence);
    int phraseIdx = 0;
    int found = 0;
    if (0 < numPhrases)
    {
        do
        {
            intptr phrase = iSPCH_GetOffset8(sentence, sentence + 4, phraseIdx);
            int j = 0;
            intptr p = phrase;
            if (((unsigned int)*(unsigned char *)(phrase + 2) & 0xf) == paramIdx)
                return 1;
            do
            {
                j = j + 1;
                if (((unsigned int)*(unsigned char *)(p + 4) & 0xf) == paramIdx)
                {
                    found = 1;
                    break;
                }
                p = phrase + j;
            } while (j < 4);
            phraseIdx = phraseIdx + 1;
        } while (phraseIdx < numPhrases);
    }
    return found;
}

/* iSPCH_GetRuleID @0x8010B220 : the rule-id byte at `index` (< 8) of a sentence's rule data, or 0xffffffff. */
extern "C" unsigned int iSPCH_GetRuleID(intptr sentence, int index)
{
    unsigned int result = 0xffffffff;
    intptr ruleData = iSPCH_GetRuleDataAddr(sentence);
    if ((unsigned int)index < 8)
        result = (unsigned int)*(unsigned char *)(index * 2 + ruleData);
    return result;
}

/* iSPCH_RuleSet @0x8010B294 : for each type-0/3 rule whose parameter the (offset) sentence uses, fire the
 *   gSentenceRuleSet callback with that rule + the parameter value from val[]. */
extern "C" void iSPCH_RuleSet(short *sentence, int rule, int *values)
{
    if (gSentenceRuleSet != 0)
    {
        char numRules = *(char *)((intptr)sentence + 7);
        int i = 0;
        unsigned char *rd = (unsigned char *)iSPCH_GetRuleDataAddr((intptr)sentence);
        intptr offSent = iSPCH_GetOffset16((intptr)sentence, (intptr)(sentence + 6), rule);
        if (0 < numRules)
        {
            do
            {
                unsigned char ruleByte = *rd;
                unsigned int paramIdx = (unsigned int)(rd[1] & 0xf);
                unsigned int ruleType = (unsigned int)(rd[1] >> 4);
                if (ruleType == 0 || ruleType == 3)
                {
                    if (iSPCH_SentenceUsesParm(offSent, paramIdx) != 0)
                    {
                        ((void (*)(int, int, int))gSentenceRuleSet)((int)(unsigned short)*sentence, (int)(unsigned int)ruleByte, values[paramIdx]);
                    }
                }
                i = i + 1;
                rd = rd + 2;
            } while (i < numRules);
        }
    }
}

/* iSPCH_GetRuleSettings @0x8010B3CC : evaluate rule types 1..12 of `sentence` against the gSentenceRuleTest
 *   callback (using values[] for the typed ones) and pack the pass/fail bits into *out. */
extern "C" unsigned int iSPCH_GetRuleSettings(short *sentence, int *values, char *out)
{
    char numRules = *(char *)((intptr)sentence + 7);
    unsigned int failed = 0;
    unsigned int passed = 0;
    unsigned char *ruleData = (unsigned char *)iSPCH_GetRuleDataAddr((intptr)sentence);
    int *valueBase = values;
    unsigned int ruleType = 1;
    do
    {
        int i = 0;
        unsigned char *p = ruleData;
        values = values + 1;
        if (0 < numRules)
        {
            do
            {
                unsigned int paramIdx = (unsigned int)(p[1] & 0xf);
                int v = 0;
                int doTest = 0;
                if (ruleType == 0xc)
                {
                    if (paramIdx == 0)
                        doTest = 1;
                }
                else if (paramIdx == ruleType)
                {
                    v = *values;
                    doTest = 1;
                }
                if (doTest)
                {
                    unsigned int bit = 1u << ((7 - i) & 0x1f);
                    if ((unsigned int)(p[1] >> 4) == 4)
                    {
                        if (valueBase[paramIdx] != 0)
                            passed |= bit;
                    }
                    else
                    {
                        int r;
                        if (gSentenceRuleTest == 0)
                            r = -1;
                        else
                            r = ((int (*)(int, int, int))gSentenceRuleTest)((int)(unsigned short)*sentence, (int)*p, v);
                        if (0 < r)
                            passed |= bit;
                        else if (r < 0)
                            failed |= bit;
                    }
                }
                i = i + 1;
                p = p + 2;
            } while (i < numRules);
        }
        ruleType = ruleType + 1;
        if (0xc < (int)ruleType)
        {
            *out = (char)failed;
            return passed & 0xff;
        }
    } while (true);
}

/* iSPCH_CheckSentenceRules @0x8010B58C : 1 if (rule[+2] ^ testVal) masked by rule[+1] and ~clearMask is 0. */
extern "C" unsigned int iSPCH_CheckSentenceRules(int testVal, int clearMask, intptr rulePtr)
{
    return (unsigned int)((((unsigned int)*(unsigned char *)(rulePtr + 2) ^ (unsigned int)testVal) & (unsigned int)*(unsigned char *)(rulePtr + 1) & ~clearMask) == 0);
}

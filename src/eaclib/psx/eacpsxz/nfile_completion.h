#ifndef NFSHS_NFILE_COMPLETION_H
#define NFSHS_NFILE_COMPLETION_H

#include "psx.h"

typedef void (*NFSHS_FileCompletion)(unsigned int id, int status, intptr param);

extern "C" void FILE_callbackop(unsigned int id, NFSHS_FileCompletion callback);

// Marshal the original three words without casting function pointers
template <typename Function, Function Callback> struct NFSHS_FileCompletionAdapter;

template <typename Result, typename Id, typename Param, Result (*Callback)(Id, int, Param)>
struct NFSHS_FileCompletionAdapter<Result (*)(Id, int, Param), Callback>
{
    static void Invoke(unsigned int id, int status, intptr param)
    {
        Callback((Id)id, status, (Param)param);
    }
};

#define NFSHS_FILE_COMPLETION(callback) \
    NFSHS_FileCompletionAdapter<decltype(&callback), &callback>::Invoke

#endif

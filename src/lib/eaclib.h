/* lib/eaclib.h — EA runtime functions (LINK_OPAQUE) */
#ifndef _EACLIB_H_
#define _EACLIB_H_
#include "../nfs4_types.h"
#include "libfns.h"
#include "snd.h"

/* -- EACPSXZ -- */
/* fixdmult */
/* trnspos */
/* fixddiv */
void FREE_find(void *arg0);                                                                             /* memstd */
void FREE_findlargest(void *arg0);                                                                      /* memstd */
void FREE_add(void *arg0);                                                                              /* memstd */
void FREE_remove(void *arg0);                                                                           /* memstd */
void initmemblock(void *arg0);                                                                          /* memstd */
void MEM_infosize(int arg0);                                                                            /* memstd */
void MEM_tailsize(char *arg0);                                                                          /* memstd */
void creatememclass(int arg0);                                                                          /* memstd */
                                                                                                        /* memstd */
void getblocksize(void *arg0);                                                                          /* memstd */
void getblockname(void *arg0);                                                                          /* memstd */
                                                                                                        /* memstd */
                                                                                                        /* memstd */
void filesizeatomic(int arg0);                                                                          /* nsync */
                                                                                                        /* nsync */
intptr loadfileadratomic(int retry, void *args);                                                        /* nsync */
                                                                                                        /* nsync */
                                                                                                        /* nsync */
intptr loadfileatadratomic(int retry, void *args);                                                      /* nsync */
                                                                                                        /* nsync */
                                                                                                        /* nsync */
intptr loadbigfileheaderatomic(int retry, void *args);                                                  /* nsync */
                                                                                                        /* nsync */
                                                                                                        /* xform */
                                                                                                        /* atanfunc */
                                                                                                        /* nloadpk */
                                                                                                        /* nloadpk */
void typeofbigfile(void *arg0);                                                                         /* locatbig */
void sizeofbigfileheader(void *arg0);                                                                   /* locatbig */
                                                                                                        /* locatbig */
                                                                                                        /* locatbig */
void locatebigoffset(void *arg0);                                                                       /* locatbig */
                                                                                                        /* locatbig */
                                                                                                        /* locatbig */
                                                                                                        /* blkmov */
                                                                                                        /* systask */
                                                                                                        /* systask */
                                                                                                        /* systask */
                                                                                                        /* random */
                                                                                                        /* random */
                                                                                                        /* timer */
void elapsedticks();                                                                                    /* timer */
void resettick();                                                                                       /* timer */
                                                                                                        /* timer */
                                                                                                        /* wildcard */
void synccallback(int arg0);                                                                            /* syncfile */
int syncblockio(intptr handle, unsigned int offset, intptr dest, int length, int priority, void *iofn); /* syncfile */
                                                                                                        /* syncfile */
                                                                                                        /* syncfile */
                                                                                                        /* syncfile */
int FILE_sizesync(int handle, int priority);                                                            /* syncfile */
                                                                                                        /* syncfile */
                                                                                                        /* syncfile */
                                                                                                        /* crossprd */
                                                                                                        /* fxform */
                                                                                                        /* fxform */
                                                                                                        /* fxform */
void intarcsin(int arg0);                                                                               /* asinfunc */
                                                                                                        /* asinfunc */
                                                                                                        /* isincos */
                                                                                                        /* trnsfrm */
                                                                                                        /* addtimer */
                                                                                                        /* addtimer */
void initgp();                                                                                          /* savegp */
                                                                                                        /* savegp */
                                                                                                        /* savegp */
                                                                                                        /* fixdsqrt */
                                                                                                        /* locatshp */
                                                                                                        /* locatshp */
                                                                                                        /* nfile */
void FILE_initwithmem(int arg0);                                                                        /* nfile */
void FILE_overhead(int arg0);                                                                           /* nfile */
                                                                                                        /* nfile */
                                                                                                        /* nfile */
void FILE_callbackop(int arg0);                                                                         /* nfile */
void FILE_priorityop(int arg0);                                                                         /* nfile */
void FILE_cancelop(int arg0);                                                                           /* nfile */
void FILE_waitop(int arg0);                                                                             /* nfile */
                                                                                                        /* nfile */
void FILE_open(char *arg0);                                                                             /* nfile */
void FILE_close(void *arg0);                                                                            /* nfile */
                                                                                                        /* nfile */
void FILE_size(char *arg0);                                                                             /* nfile */
void iFILE_addbigreadcallback(int arg0);                                                                /* nfile */
void iFILE_addbigopencallback(int arg0);                                                                /* nfile */
void FILE_addbig(char *arg0);                                                                           /* nfile */
void iFILE_delbigclosecallback(int arg0);                                                               /* nfile */
void FILE_delbig(char *arg0);                                                                           /* nfile */
intptr FILE_atomic(intptr fn, int idle, int retries, void *args);                                       /* nfile */
void iFILE_ExecCommand(void *arg0);                                                                     /* nfile */
void iFILE_CommandCompleteCallback(int arg0);                                                           /* nfile */
void iFILE_perror();                                                                                    /* nfile */
void reserveop(char *arg0);                                                                             /* nfile */
void freeop(void *arg0);                                                                                /* nfile */
void reservehandle(int arg0);                                                                           /* nfile */
void freehandle(void *arg0);                                                                            /* nfile */
                                                                                                        /* fixdinv */
                                                                                                        /* fixdsin */
                                                                                                        /* fixdsin */
                                                                                                        /* fixdatan */
void addmatrix(int *arg0);                                                                              /* matrix */
void submatrix(int *arg0);                                                                              /* matrix */
void scalematrix(int *arg0);                                                                            /* matrix */
                                                                                                        /* matrix */
                                                                                                        /* primate */
                                                                                                        /* primate */
                                                                                                        /* primate */
                                                                                                        /* movf */
                                                                                                        /* shpsubs */
                                                                                                        /* shpsubs */
void queueadd(void *arg0);                                                                              /* nasync */
void queuefetch(void *arg0);                                                                            /* nasync */
void newrequestid(void *arg0);                                                                          /* nasync */
void locaterequest(void *arg0);                                                                         /* nasync */
void cancelrequest(void *arg0);                                                                         /* nasync */
void finishrequest(void *arg0);                                                                         /* nasync */
void loadfileclosecallback(int arg0);                                                                   /* nasync */
void loadfilereadcallback(int arg0);                                                                    /* nasync */
void loadfilesizecallback(int arg0);                                                                    /* nasync */
void loadfileopencallback(int arg0);                                                                    /* nasync */
void loadsegreadcallback(int arg0);                                                                     /* nasync */
void asyncsystemtask();                                                                                 /* nasync */
                                                                                                        /* nasync */
void asyncloadfilecallback(char *arg0);                                                                 /* nasync */
                                                                                                        /* nasync */
void asyncloadfileatcallback(char *arg0);                                                               /* nasync */
                                                                                                        /* nasync */
                                                                                                        /* nasync */
void asyncloadsegmentcallback(int arg0);                                                                /* nasync */
                                                                                                        /* nasync */
                                                                                                        /* nasync */
                                                                                                        /* nasync */
                                                                                                        /* nasync */
                                                                                                        /* blkfill */
                                                                                                        /* blkfill */
                                                                                                        /* sinfunc */
                                                                                                        /* sinfunc */
                                                                                                        /* resize */
                                                                                                        /* loadshp */
void addexit(void *arg0);                                                                               /* exit */
                                                                                                        /* textset */
                                                                                                        /* getm */
                                                                                                        /* getm */
void putm(void *arg0);                                                                                  /* textcrnt */
void puti(void *arg0);                                                                                  /* textcrnt */
                                                                                                        /* isqrt */
                                                                                                        /* fsincos */
                                                                                                        /* joystkn */
void initfileio(void *arg0);                                                                            /* fileroot */
                                                                                                        /* fileroot */
void openfile(char *arg0);                                                                              /* fileroot */
void closefile(int arg0);                                                                               /* fileroot */
void readfile(int arg0);                                                                                /* fileroot */
void readfile_systask();                                                                                /* fileroot */
void writefile(int arg0);                                                                               /* fileroot */
void getfilesize(int arg0);                                                                             /* fileroot */
void stopreadfile(int arg0);                                                                            /* fileroot */
void MEM_defaultevent(int arg0);                                                                        /* meminit */
                                                                                                        /* inittmr */
                                                                                                        /* inittmr */
void restoretimer();                                                                                    /* inittmr */
void tmrint(int arg0);                                                                                  /* inittmr */
                                                                                                        /* shpdepth */
charactertbl *textbsearch(unsigned int key, charactertbl *base, int count, int stride);                 /* textfor */
                                                                                                        /* textfor */
                                                                                                        /* unhuff */
void memcpyl(void *arg0);                                                                               /* unhuff */
void memcpyb(void *arg0);                                                                               /* unhuff */
void refcpy(void *arg0);                                                                                /* unhuff */
                                                                                                        /* unref */
unsigned char *chase(int code);                                                                         /* unref */
                                                                                                        /* unbtree */
                                                                                                        /* nullfunc */
                                                                                                        /* crc */
unsigned int checkrect(void *rect);                                                                     /* vramfxya */
int vramimage(void *rect, void *data);                                                                  /* vramfxya */
                                                                                                        /* vramfxya */
void getshapeclut(void *arg0);                                                                          /* shpclut */
                                                                                                        /* shpclut */
void CD_systaskfunc();                                                                                  /* cdfs */
void CD_timerfunc();                                                                                    /* cdfs */
void CdReadyHandler(unsigned char intr, unsigned char *result);                                         /* cdfs */
void readsectorB();                                                                                     /* cdfs */
void loaddirinfo(int startSector, int numSectors, int maxEntries);                                      /* cdfs */
void dircompare(void *arg0);                                                                            /* cdfs */
void CD_Restore();                                                                                      /* cdfs */
void CD_Init(int arg0);                                                                                 /* cdfs */
void CD_Restart(int arg0);                                                                              /* cdfs */
void CD_Open(void *arg0);                                                                               /* cdfs */
void CD_Close(int arg0);                                                                                /* cdfs */
void CD_Read(int arg0);                                                                                 /* cdfs */
void CD_Stopread();                                                                                     /* cdfs */
void CD_Getinfo(int arg0);                                                                              /* cdfs */
void cluttype(int arg0);                                                                                /* cluttype */
void shapetype(int arg0);                                                                               /* shptype */
void validatehandle(void *arg0);                                                                        /* stream */
void inbetween(void *arg0);                                                                             /* stream */
void decbufferusage(void *arg0);                                                                        /* stream */
void getfreerequest(void *arg0);                                                                        /* stream */
void queuerequest(void *arg0);                                                                          /* stream */
// dup: void locaterequest(void * arg0);   /* stream */
void freerequest(void *arg0);                           /* stream */
void filterchunk(void *arg0);                           /* stream */
void parsechunks(void *arg0);                           /* stream */
void opencallback(int arg0);                            /* stream */
void closecallback(int arg0);                           /* stream */
void readcallback(int arg0);                            /* stream */
void startnextrequest(void *arg0);                      /* stream */
void restartstream(void *arg0);                         /* stream */
void STREAM_overhead(int arg0);                         /* stream */
void STREAM_create(int arg0);                           /* stream */
void STREAM_setfilter(void *arg0);                      /* stream */
void STREAM_destroy(void *arg0);                        /* stream */
void STREAM_setpriority(void *arg0);                    /* stream */
void STREAM_setgreedylevel(void *arg0);                 /* stream */
void STREAM_setgreedystate(void *arg0);                 /* stream */
void STREAM_queuefile(void *arg0);                      /* stream */
void STREAM_queuemem(void *arg0);                       /* stream */
void STREAM_cancelrequest(void *arg0);                  /* stream */
void STREAM_kill(void *arg0);                           /* stream */
void STREAM_get(int arg0);                              /* stream */
void STREAM_release(void *arg0);                        /* stream */
void STREAM_gettable(void *arg0);                       /* stream */
void STREAM_state(void *arg0);                          /* stream */
void STREAM_isendofstream(void *arg0);                  /* stream */
void STREAM_buffersize(void *arg0);                     /* stream */
void STREAM_bufferusage(void *arg0);                    /* stream */
void iscurrentthread(int arg0);                         /* threads */
void yieldthread();                                     /* threads */
void allocmutex();                                      /* callback */
void freemutex(void *arg0);                             /* callback */
void make64(void *arg0);                                /* math64a */
void divu64(int arg0);                                  /* math64a */
void stricmp(char *arg0);                               /* stricmp */
void transmult(void *arg0);                             /* trnsmult */
intptr fastmovfxya(unsigned char *shape, int x, int y); /* fastmovf */
int decodeansi(unsigned char **cursor);                 /* textcode */
void remapshiftjiscode(int arg0);                       /* isqrttbl */
int decodeshiftjis(unsigned char **cursor);             /* isqrttbl */
void psxdevelopmentsystem();                            /* devsys */
/* -- SNDPSXZ -- */
void iSNDremovepatches(int arg0);                                                                                                                 /* sbremove */
                                                                                                                                                  /* sbremove */
void cSNDbankremove(int arg0);                                                                                                                    /* sbremove */
                                                                                                                                                  /* splysdef */
                                                                                                                                                  /* span */
void iSNDunsafevol(int arg0);                                                                                                                     /* svol */
                                                                                                                                                  /* svol */
                                                                                                                                                  /* sstsetpr */
                                                                                                                                                  /* seffect */
                                                                                                                                                  /* seffect */
void iSNDunsafebend(int arg0);                                                                                                                    /* sbend */
                                                                                                                                                  /* sbend */
                                                                                                                                                  /* splay */
void cSNDplay(void *arg0);                                                                                                                        /* splay */
                                                                                                                                                  /* sover */
                                                                                                                                                  /* sbhdrsze */
                                                                                                                                                  /* sbhdrcpy */
                                                                                                                                                  /* sdmemlu */
                                                                                                                                                  /* sbadd */
                                                                                                                                                  /* sstop */
                                                                                                                                                  /* spitch */
                                                                                                                                                  /* smasterv */
                                                                                                                                                  /* s3dlow */
void SNDstopall();                                                                                                                                /* sstopall */
                                                                                                                                                  /* sautovol */
                                                                                                                                                  /* sstgetv */
                                                                                                                                                  /* sststat */
                                                                                                                                                  /* sstrstat */
void strrstr(char *arg0);                                                                                                                         /* sstrstat */
void iSNDstreamdestroyall();                                                                                                                      /* sst */
SndStreamState *iSNDstreamgetstreamptr(int index);                                                                                                /* sst */
int iSNDstreamremoverequest(unsigned int requestId);                                                                                              /* sst */
void iSNDstreamreleasecallback(intptr sample);                                                                                                    /* sst */
void iSNDstreamnotifycallback(int player, unsigned int bytes);                                                                                    /* sst */
int iSNDstreamparseheader(SndStreamState *stream, intptr data);                                                                                   /* sst */
int iSNDstreamparsenumchunks(SndStreamState *stream, intptr data);                                                                                /* sst */
void iSNDstreamparsedata(SndStreamState *stream, intptr chunk);                                                                                   /* sst */
int iSNDstreamparseend(SndStreamState *stream, intptr chunk);                                                                                     /* sst */
int iSNDstreamparsechunk(SndStreamState *stream, intptr chunk);                                                                                   /* sst */
int iSNDstreamisheld(SndStreamState *stream);                                                                                                     /* sst */
void iSNDstreamhotroddatachunks();                                                                                                                /* sst */
void iSNDstreamservice();                                                                                                                         /* sst */
void iSNDstreamnumcreated();                                                                                                                      /* sst */
int iSNDstreamcreate(int *priority, int numRequests, int packetArg, intptr objectBuffer, int memorySize, int externalHandle, int externalFlag);   /* sst */
int iSNDstreamqueue(unsigned int stream, int name, char *filename, int offset, int mode);                                                         /* sst */
                                                                                                                                                  /* spvoices */
                                                                                                                                                  /* spvoices */
                                                                                                                                                  /* spvoices */
                                                                                                                                                  /* spvoices */
                                                                                                                                                  /* sstsetgl */
                                                                                                                                                  /* sstsetgs */
                                                                                                                                                  /* sstautov */
                                                                                                                                                  /* slimits */
                                                                                                                                                  /* slimits */
void SNDSTRM_overheadtap(int arg0);                                                                                                               /* sstovrhd */
                                                                                                                                                  /* sstovrhd */
                                                                                                                                                  /* sstvol */
void iSNDserver();                                                                                                                                /* sserver */
void iSND100hzserver();                                                                                                                           /* sserver */
void iSNDenteraudio();                                                                                                                            /* sserver */
void iSNDleaveaudio();                                                                                                                            /* sserver */
                                                                                                                                                  /* sserver */
                                                                                                                                                  /* sserver */
                                                                                                                                                  /* stimerem */
                                                                                                                                                  /* ssysinit */
                                                                                                                                                  /* ssysinit */
                                                                                                                                                  /* ssysinit */
                                                                                                                                                  /* ssysinit */
void iSNDsystemtaskreal();                                                                                                                        /* ssysreal */
                                                                                                                                                  /* ssysreal */
void SNDcdvol(int arg0);                                                                                                                          /* scdvol */
void iSNDplatformfree(void *arg0);                                                                                                                /* sdata */
void iSNDsync_func(int arg0);                                                                                                                     /* sbirmpat */
void iSNDvalidbank(int arg0);                                                                                                                     /* sbvalid */
void iSNDischanreserved(int arg0);                                                                                                                /* salloc */
void iSNDallocchan(int arg0);                                                                                                                     /* salloc */
intptr iSNDfreechan(int chan);                                                                                                                    /* salloc: mixed status/address result */
void iSNDgetchan(int arg0);                                                                                                                       /* salloc */
void iSNDplatform3dpos(int arg0);                                                                                                                 /* s3dpos */
int iSNDpatchkey(int chan, int *iter);                                                                                                            /* spatkey */
void iSNDcalcvol(int arg0);                                                                                                                       /* spatkey */
void iSNDpsxkeyon(int arg0);                                                                                                                      /* spatkey */
void iSNDpsxkeyoff(int arg0);                                                                                                                     /* spatkey */
void iSNDpsxeffecton(int arg0);                                                                                                                   /* spatkey */
void iSNDpsxeffectoff(int arg0);                                                                                                                  /* spatkey */
void iSNDpsxeffectvol(int arg0);                                                                                                                  /* spatkey */
void iSNDsetvol(int arg0);                                                                                                                        /* spatkey */
void iSNDsetslot(int arg0);                                                                                                                       /* spatkey */
void iSNDstartvoice(int arg0);                                                                                                                    /* spatkey */
void iSNDplatformoutputcaps(void *arg0);                                                                                                          /* slib */
void iSNDplatformoutputset(void *arg0);                                                                                                           /* slib */
void iSNDinit(void *arg0);                                                                                                                        /* slib */
void iSNDrestore();                                                                                                                               /* slib */
void iSNDserve();                                                                                                                                 /* slib */
void iSNDstop(int arg0);                                                                                                                          /* sdriver */
void iSNDplatformpitch(int arg0);                                                                                                                 /* sdriver */
void iSNDplatformfxlevel(int arg0);                                                                                                               /* sdriver */
void iSNDvol(void *arg0);                                                                                                                         /* sdriver */
void SNDI_mutexalloc();                                                                                                                           /* sdfx */
void SNDI_mutexfree();                                                                                                                            /* sdfx */
void SNDI_mutexlock();                                                                                                                            /* sdfx */
void SNDI_mutexunlock();                                                                                                                          /* sdfx */
void iSNDpsxfxinit(int arg0);                                                                                                                     /* sdfx */
void iSNDplatformfxinit(int arg0);                                                                                                                /* sdfx */
void iSNDplatformfxmasterlevel(int arg0);                                                                                                         /* sfxlevel */
void SNDfxlevel(int arg0);                                                                                                                        /* sfxlevel */
void iSNDdetunetolinear(int arg0);                                                                                                                /* sclcptch */
void iSNDcalcpitch(int arg0);                                                                                                                     /* sclcptch */
void iSNDresetpatch(SndTimbre *patch);                                                                                                            /* stagpat */
unsigned char *iSNDresettimbre(SndTimbre *timbre, SndTimbre *buffer);                                                                             /* stagpat */
intptr iSNDresolveheader(SndTimbre *timbre, const SndTimbre *header);                                                                             /* stagpat */
void iSNDfindfreekey(void);                                                                                                                       /* stagpat */
int iSNDplaytaggedtimbre(intptr stream, const unsigned char *tag, SndTimbre *timbre, SndTimbre *header, int note, int velocity, int pitchOffset); /* stagpat */
int iSNDplaytaggedpatch(unsigned char *patch, int *info);                                                                                         /* stagpat */
int iSNDresolvetaggedpatch(unsigned char *bank, intptr patchBase, int *scratch);                                                                  /* stagpat */
int iSNDremovetaggedpatch(unsigned char *bank, int *patch);                                                                                       /* stagpat */
int iSNDdownloadbank(intptr bankData, intptr patchData);                                                                                          /* sbdload */
void iSNDbankalloc();                                                                                                                             /* sballoc */
void SNDgetvol(int arg0);                                                                                                                         /* sgetvol */
void iSNDpacketplayoverhead(int arg0);                                                                                                            /* spktplay */
void SNDPKTPLAY_overhead(int arg0);                                                                                                               /* spktplay */
int SNDPKTPLAY_create(intptr memory, int memorySize, SndPacketReleaseCallback release, SndPacketNotifyCallback notify);                           /* spktplay */
int SNDPKTPLAY_start(int player, intptr rate, intptr header, int *params);                                                                        /* spktplay */
int SNDPKTPLAY_submit(int player, intptr *frame);                                                                                                 /* spktplay */
void SNDPKTPLAY_submitspace(int arg0);                                                                                                            /* spktplay */
void SNDPKTPLAY_unsafeframesoutstanding(int arg0);                                                                                                /* spktplay */
void SNDPKTPLAY_framesoutstanding(int arg0);                                                                                                      /* spktplay */
void SNDPKTPLAY_purge(int arg0);                                                                                                                  /* spktplay */
void SNDPKTPLAY_stop(int arg0);                                                                                                                   /* spktplay */
void SNDPKTPLAY_destroy(int arg0);                                                                                                                /* spktplay */
intptr iSNDpacketget(int player, int channel, int *frameSize);                                                                                    /* spktplay */
unsigned int iSNDpacketfreeframes(int player, int channel, int bytes);                                                                            /* spktplay */
void iSNDmulu64(void *arg0);                                                                                                                      /* smath64 */
void iSNDdivu64(int arg0);                                                                                                                        /* smath64 */
SndStreamRequest *iSNDstreamgetrequestptr(unsigned int requestId);                                                                                /* sstgetrp */
void SNDattributessetdef(void *arg0);                                                                                                             /* spat2hdr */
void iSNDpatchtohdr(void *arg0);                                                                                                                  /* spat2hdr */
void iSNDpacketgetirq();                                                                                                                          /* sdpacket */
void iSNDpacketsetirq();                                                                                                                          /* sdpacket */
void iSNDpacketirqcallback();                                                                                                                     /* sdpacket */
void iSNDpsxzerospu(void *arg0);                                                                                                                  /* sdpacket */
void iSNDpacketpurgeframes(int arg0);                                                                                                             /* sdpacket */
int iSNDfillspuwithpackets(int player, int chunk);                                                                                                /* sdpacket */
void iSNDpacketserve();                                                                                                                           /* sdpacket */
void iSNDplatformpacketoverhead();                                                                                                                /* sdpacket */
void iSNDplatformcalcdatarate(void *arg0);                                                                                                        /* sdpacket */
int iSNDplatformpacketplaycreate(int player, int *memory);                                                                                        /* sdpacket */
void iSNDplatformpacketplaydestroy(int arg0);                                                                                                     /* sdpacket */
void iSNDplatformpacketplay(char arg0);                                                                                                           /* sdpacket */
void iSNDpsxpacketstop(void *arg0);                                                                                                               /* sdpacket */
void iSNDserveraddclient(void *arg0);                                                                                                             /* ssysserv */
void iSNDserverremoveclient(void *arg0);                                                                                                          /* ssysserv */
void SNDSYS_service();                                                                                                                            /* ssysserv */
void iSNDtimeremaining(int arg0);                                                                                                                 /* sdtimrem */
void iSNDmemconstrain(int *arg0);                                                                                                                 /* smemman */
void iSNDmeminit(void *arg0);                                                                                                                     /* smemman */
void iSNDmemrestore();                                                                                                                            /* smemman */
void iSNDmalloc(int arg0);                                                                                                                        /* smemman */
void iSNDplatformcdpanvol(int arg0);                                                                                                              /* sdcdvol */
void iSNDpsxmemconstrain(int *arg0);                                                                                                              /* sdmemman */
void iSNDpsxmalloc(int arg0);                                                                                                                     /* sdmemman */
void iSNDpsxfree(int arg0);                                                                                                                       /* sdmemman */
void iSNDdmtransfer();                                                                                                                            /* sdma */
void iSNDdmcallback();                                                                                                                            /* sdma */
void iSNDdmservice(void *arg0);                                                                                                                   /* sdma */
int iSNDdmqueue(intptr srcRam, int dstSpu, int len, unsigned char priority, unsigned char flag);                                                  /* sdma */
int iSNDdmqueuesplit(intptr srcRam, int dstSpu, int len, unsigned char priority);                                                                 /* sdma */
void iSNDdmcomplete(int arg0);                                                                                                                    /* sdma */
void iSNDabs(int arg0);                                                                                                                           /* saetodv */
void iSNDatodlrv(int arg0);                                                                                                                       /* saetodv */
void iSNDatolrv(int arg0);                                                                                                                        /* saetolrv */
int iSNDplatformresolve(intptr cursor, intptr bank, int *patch);                                                                                  /* sdresolv */
int iSNDplatformremove(intptr cursor, int *patch);                                                                                                /* sdresolv */
int iSNDplatformplay(intptr stream, int voice, int level, int pitch, int sampleArg, int fx, int volAngle, int volDelta);                          /* sdplapat */
void randrange(int arg0);                                                                                                                         /* srrange */
int iSNDgettag(intptr *cursor, unsigned int *id, int *value, intptr *data);                                                                       /* sgettag */
void iSNDrandom();                                                                                                                                /* srandom */
void iSNDpsxenablespuirq();                                                                                                                       /* sdspuirq */
void iSNDpsxdisablespuirq();                                                                                                                      /* sdspuirq */
void iSNDpvtolrv(int arg0);                                                                                                                       /* spvtolrv */
void iSNDlibatodlrv(int arg0);                                                                                                                    /* saelib */
void iSNDgetdata(void *arg0);                                                                                                                     /* sgetdata */
void iSNDsin(int arg0);                                                                                                                           /* ssine */
/* -- SPCHPSXZ -- */
int VoxEvent_GetFilterLengthFlag(intptr event);                             /* spchevnt */
unsigned int VoxEvent_GetKeepTillExpiresFlag(intptr event);                 /* spchevnt */
intptr iSPCH_SearchEventDat(intptr dat, unsigned int eventID);              /* spchevnt */
intptr iSPCH_FindEvent(unsigned int eventID);                               /* spchevnt */
void iSPCH_InitEventDat();                                                  /* spchevnt */
int GetFilterLength();                                                      /* spchevnt */
int GetFilterPriority();                                                    /* spchevnt */
void iSPCH_InitEventQueue();                                                /* spchevnt */
void iSPCH_FindEventSlot(int arg0);                                         /* spchevnt */
int SPCH_AddEvent(unsigned int *table);                                     /* spchevnt */
int iSPCH_ChooseEvent();                                                    /* spchevnt */
void SPCH_ClearEventQueue();                                                /* spchevnt */
void iSPCH_ClearOldEvents(int arg0);                                        /* spchevnt */
void SPCH_PlaySpeech();                                                     /* spchevnt */
void SPCH_ChooseSpeech();                                                   /* spchevnt */
void iSPCH_InitBanks();                                                     /* spchbank */
void iSPCH_DisposeBanks();                                                  /* spchbank */
intptr iSPCH_BankMemAlloc(unsigned int numBanks);                           /* spchbank */
void iSPCH_GetFreeBank();                                                   /* spchbank */
void iSPCH_FindBank(int arg0);                                              /* spchbank */
void iSPCH_TestSubBankBounds(int arg0);                                     /* spchbank */
void iSPCH_SetCycleBits(intptr bank);                                       /* spchbank */
int SPCH_AddBank(intptr bank);                                              /* spchbank */
intptr iSPCH_MemAlloc(int numBytes, char *message);                         /* spchinit */
void iSPCH_MemFree(void *arg0);                                             /* spchinit */
void SPCH_Deinit();                                                         /* spchinit */
void iSPCH_InitInGame();                                                    /* spchinit */
void SPCH_GetSampleDataRate(int arg0);                                      /* spchinit */
intptr SPCH_InitBankMem(intptr memAllocFn, intptr memFreeFn, int numBanks); /* spchinit */
int SPCH_Init(intptr sampleRequestCb, unsigned int gameNum, int dataRate);  /* spchinit */
int iSPCH_EACrandom();                                                      /* spchrand */
int *iSPCH_EACseedrandom(unsigned int seed);                                /* spchrand */
int iSPCH_Rand(int n);                                                      /* spchrand */
int iSPCH_BindData(unsigned short *dat);                                    /* spchrand */
void SPCH_ResolveData(void *arg0);                                          /* spchrslv */
int iSPCH_GetMatchValue(intptr base, int index);                            /* spchdata */
int VoxSentence_GetShortRule(intptr sentence);                              /* spchdata */
int VoxSentence_GetNumPhrases(intptr sentence);                             /* spchdata */
// dup: void VoxEvent_GetFilterLengthFlag(void * arg0);   /* spchdata */
intptr iSPCH_GetOffset8(intptr base, intptr tableBase, int index); /* spchdata */
// dup: void iSPCH_GetOffset16(void * arg0);   /* spchdata */
void iSPCH_MatchSample(int arg0);                                                                                                 /* spchpick */
void iSPCH_GetPhraseBank(void *arg0);                                                                                             /* spchpick */
intptr iSPCH_GetBankBits(intptr bank);                                                                                            /* spchpick */
void iSPCH_ClearCycleBit(void *arg0);                                                                                             /* spchpick */
void iSPCH_CheckBankBit(void *arg0);                                                                                              /* spchpick */
void iSPCH_CheckTemplateSample(void *arg0);                                                                                       /* spchpick */
void iSPCH_SampleExists(void *arg0);                                                                                              /* spchpick */
void iSPCH_ChooseSamples(void *arg0);                                                                                             /* spchpick */
void iSPCH_SampleLength(void *arg0);                                                                                              /* spchpick */
void iSPCH_ConvertTime(int arg0);                                                                                                 /* spchpick */
int iSPCH_SentenceLength(intptr sentence);                                                                                        /* spchpick */
unsigned char *iSPCH_OrderSentences(intptr event, unsigned char *outOrder);                                                       /* spchpick */
void iSPCH_RepeatEvent(void *arg0);                                                                                               /* spchpick */
int iSPCH_ShortRuleStatus(intptr sentence, int mode);                                                                             /* spchpick */
int iSPCH_SentenceGetChoices(intptr sentence, intptr paramTable, unsigned int ruleByte1, unsigned int ruleByte2, int filterMode); /* spchpick */
void iSPCH_RandomizeSentencePicks(intptr sentence);                                                                               /* spchpick */
void iSPCH_IterateChoice(intptr sentence);                                                                                        /* spchpick */
int iSPCH_ChooseShortSentence(intptr sentence);                                                                                   /* spchpick */
int iSPCH_SentenceMakeChoice(intptr sentence, int mode);                                                                          /* spchpick */
void iSPCH_ConstantRuleSet(short *sentence, intptr rule);                                                                         /* spchpick */
int iSPCH_MakeSampleRequests(intptr sentence, int paramTable);                                                                    /* spchpick */
void iSPCH_ClearChosen();                                                                                                         /* spchpick */
int iSPCH_SaveChosenSentence(intptr event, intptr sentence, int ruleCtx, int *eventArgs);                                         /* spchpick */
void iSPCH_OneChosen();                                                                                                           /* spchpick */
void iSPCH_PlayChosen(void *arg0);                                                                                                /* spchpick */
void iSPCH_ChooseSentence(void *arg0);                                                                                            /* spchpick */
void SPCH_SetPreLoadTicks(int arg0);                                                                                              /* spchpick */
// dup: void VoxSentence_GetNumPhrases(void * arg0);   /* spchrule */
// dup: void iSPCH_GetOffset8(void * arg0);   /* spchrule */
// dup: void iSPCH_GetOffset16(void * arg0);   /* spchrule */
intptr iSPCH_GetRuleDataAddr(intptr sentence);                                     /* spchrule */
int iSPCH_SentenceUsesParm(intptr sentence, unsigned int paramIdx);                /* spchrule */
unsigned int iSPCH_GetRuleID(intptr sentence, int index);                          /* spchrule */
void iSPCH_RuleSet(short *sentence, int rule, int *values);                        /* spchrule */
unsigned int iSPCH_GetRuleSettings(short *sentence, int *values, char *out);       /* spchrule */
unsigned int iSPCH_CheckSentenceRules(int testVal, int clearMask, intptr rulePtr); /* spchrule */
void iSPCH_InitSample(void *arg0);                                                 /* spchsamp */
int iSPCH_UnPackSample(intptr bank, unsigned int sampleIdx, int *out);             /* spchsamp */

#endif

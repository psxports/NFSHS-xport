/* link_data.cpp -- AGGREGATION TU (Stage 2a of self-containment).
 * Typed ZERO-init storage for module-owned INITIALISED-data globals whose
 * NFS4.EXE image is all-zero (runtime-populated .data/.sdata tables) and which
 * were declared `extern` but never defined. Surfaced by the link harness.
 * Types from each symbol's extern decl. (Non-zero INIT globals -> Stage 2b.) */
#include "nfs4_types.h"

extern "C" {

int Audio_direct3davail;                                       /* @8013d4fc 4B */
tBTCPerpInfo BTCPerpInfo[2][10];                               /* @80120bc0 320B */
extern int CD_nopen;                                           /* @8013bf5c 4B */
shapetbl * CarIO_Plate1[2];                                    /* @8013d748 8B */
shapetbl * CarIO_Plate2[2];                                    /* @8013d750 8B */
int CarIO_carPixMapCount;                                      /* @8013d73c 4B */
int CarIO_carVRamCount;                                        /* @8013d740 4B */
int CarIO_licenseSFX_Count;                                    /* @8013d744 4B */
int ChangedEnabling;                                           /* @8013d2ec 4B */
int Chunk_numLight;                                            /* @8013d4ec 4B */
int DS_active;                                                 /* @8013bf68 4B */
int Device_gForcePause;                                        /* @8013d778 4B */
int Device_gPausePort;                                         /* @8013d77c 4B */
int Device_gPaused;                                            /* @8013d780 4B */
u_long Device_gPrev[2];                                        /* @8013d78c 8B */
int Device_gToggleTime[2];                                     /* @8013d784 8B */
DrawC_tEnvMap * DrawC_gEnvMap;                                 /* @8013d7f0 4B */
int DrawC_gEnvMapMax;                                          /* @8013d7f8 4B */
MATRIX DrawC_gMatA;                                            /* @8011f4e8 32B */
int DrawC_gMenuColor[2];                                       /* @8013d800 8B */
int DrawC_gMenuLights;                                         /* @8013d808 4B */
int DrawC_gMenuLightsDirection;                                /* @8013d80c 4B */
short DrawC_gOverlay[51];                                      /* @8011f508 104B */
short DrawC_gReflectOffset[2];                                 /* @8013d814 4B */
MATRIX DrawC_gScreenMat;                                       /* @8011f4c8 32B */
DrawC_tEnvMap * DrawC_gShadow;                                 /* @8013d7f4 4B */
int DrawC_gShadowMax;                                          /* @8013d7fc 4B */
int DrawC_gWetRoad;                                            /* @8013d810 4B */
int Draw_gDoVSync;                                             /* @8013d7a8 4B */
int Draw_gMaxPrim;                                             /* @8013d7c0 4B */
int Draw_gMidGroundOtz;                                        /* @8013d7bc 4B */
int Draw_gNumView;                                             /* @8013d7ac 4B */
Draw_tView Draw_gView[10];                                     /* @8011ec54 2000B */
int Draw_gViewOtSize;                                          /* @8013d7b0 4B */
COORD16 Fe3D_lightsVertex[64];                                 /* @80051334 384B */
COORD16 Fe3D_spotVertex[33];                                   /* @8005126c 200B */
FogKey Fog_gBuf[32];                                           /* @8012307c 384B */
FogKey            * Fog_gCurrentKey[2];                        /* @8013db80 8B */
FogKey            * Fog_gHeadKey;                              /* @8013db88 4B */
int Fog_gNumKeys;                                              /* @8013db7c 4B */
short Hud_NextPerp[2];                                         /* @8013d994 4B */
int MEMCARD_INITIALIZED;                                       /* @80051a80 4B */
PinkSlipsCarSelectState PinkSlipsScreenState[2];               /* @80052034 8B */
tReplayBuffer Replay_ReplayBuffer;                             /* @8011716c 27180B */
tReplayCameraModes Replay_ReplayCamera[2];                     /* @8011704c 32B */
int Replay_ReplayCounter[2];                                   /* @8013d400 8B */
int Replay_ReplayGetPtr;                                       /* @8013d3fc 4B */
tReplayInterface Replay_ReplayInterface;                       /* @8011702c 32B */
int Replay_ReplayMode;                                         /* @8013d3f4 4B */
int Replay_ReplayStorePtr;                                     /* @8013d3f8 4B */
int Replay_Size;                                               /* @8013d3ec 4B */
Stats_tPosition Stats_racePosition[6];                         /* @8011e0e0 96B */
TP_ZPaletteSystem TP_gZPaletteSystem;                          /* @8013db78 4B */
int TrackSpec_gCurrentSpec;                                    /* @8013db94 4B */
int TrackSpec_gMaxSpec;                                        /* @8013db98 4B */
int TrackSpec_gPrevSpec;                                       /* @8013db90 4B */
CTrackSpec TrackSpec_gSpec;                                    /* @8012327c 264B */
Chunk              * Track_chunkList;                          /* @8013d4b8 4B */
int Track_gControllerCount;                                    /* @8013d4e4 4B */
u_char *Track_gInViewCount;                                    /* @8013d4b0 4B */
short *Track_gInViewList;                                      /* @8013d4ac 4B */
Track_tMaterialController * Track_gMatController;              /* @8013d4e8 4B */
Trk_ObjectDef     ** Track_gObjDefs;                           /* @8013d4d4 4B */
Draw_tPixMap Track_gReflectionMaps[4];                         /* @8011e170 64B */
SaveSurface        * Track_gSaveSurface;                       /* @8013d4cc 4B */
TrackHeader            * Track_header;                         /* @8013d4b4 4B */
Track_tMaterial * Track_materials;                             /* @8013d4d0 4B */
SimpleMem              * Track_mem;                            /* @8013d4d8 4B */
int Weather_gDensityChangeFactor;                              /* @8013dbf8 4B */
int Weather_gDensityGoalState;                                 /* @8013dbf0 4B */
int Weather_gDensityTimerGoal;                                 /* @8013dc00 4B */
char             * Weather_gDrawnServer[2];                    /* @8013dbe0 8B */
int Weather_gIntensityChangeFactor;                            /* @8013dbfc 4B */
int Weather_gIntensityGoalState;                               /* @8013dbf4 4B */
int Weather_gIntensityTimerGoal;                               /* @8013dc04 4B */
SVECTOR          * Weather_gPServer[2];                        /* @8013dbd0 8B */
SVECTOR          * Weather_gPos;                               /* @8013dba8 4B */
DVECTOR          * Weather_gPrevPServer[2];                    /* @8013dbd8 8B */
int Weather_gSnowTrack;                                        /* @8013dc08 4B */
Weather_tSplatInfo * Weather_gSplatInfo;                       /* @8013dbac 4B */
Weather_tSplatInfo * Weather_gSplatInfoServer[2];              /* @8013dbc8 8B */
Weather_tSys Weather_gSys;                                     /* @80123408 36B */
int Weather_gTrackIntensityLimit;                              /* @8013dc0c 4B */
CWeatherSpec     * Weather_gTrackSpec;                         /* @8013dbc4 4B */
int Weather_gType;                                             /* @8013dbec 4B */
char             * Weather_gWasDrawn;                          /* @8013dba4 4B */
int abortflag;                                                 /* @8013dcd4 4B */
int availablefilesystems;                                      /* @8013dc60 4B */
char compressed_data[33];                                      /* @8011db98 36B */
tControllerData controlData[2];                                /* @8011706c 256B */
char               * creditShapeFile;                          /* @80052a58 4B */
int currentfilesystem;                                         /* @8013dc5c 4B */
CurrentFontState currentfont = {};                  /* @80135ba0 184B on PSX */
short download;                                                /* @80052a30 2B */
int drawpending;                                               /* @8013dd10 4B */
int exceedRedline;                                             /* @8013d300 4B */
BWorldSm_Pos      * fogslicePos;                               /* @8013db8c 4B */
u_long font_abr;                                               /* @8013d860 4B */
u_short font_currentTPage[2];                                  /* @8013d868 4B */
int frontMult;                                                 /* @8013d308 4B */
int gBrakeRatio;                                               /* @8013d2f0 4B */
int gCISouffle;                                                /* @8013d44c 4B */
Car_tObj * gCarObj[2];                                         /* @80052a68 8B */
short gClutDepth[256][16];                                     /* @8012107c 8192B */
intptr gCurrentMemory;                                    /* @8013dab8 4B on PSX */
int gCurrentNumSplats;                                         /* @8013dba0 4B */
dflip gEnviro[2];                                              /* @8011f424 48B */
int gFlip;                                                     /* @8013d7b4 4B */
u_short gFontClut;                                             /* @8013d864 2B */
u_char gFontSpaceWidth;                                        /* @8013d866 1B */
CSceneList * gGameSceneList;                                   /* @8013d408 4B */
int gGasRatio;                                                 /* @8013d2f4 4B */
tTexture_ShapeInfo * gHelpShapes;                              /* @80052a64 4B */
intptr gHighMemory;                                       /* @8013dab4 4B on PSX */
Souffle_tISouffle * gISouffle;                                 /* @8013d448 4B */
Track_tArtresource gInitialArt;                                /* @8011e158 24B */
int gLoop;                                                     /* @8013d7b8 4B */
intptr gLowMemory;                                        /* @8013dab0 4B on PSX */
tMdecHandle gMDECinfo;                                         /* @80052b28 8B */
intptr gMemAlloc;                                            /* @801370a8 4B on PSX; callback pointer carrier */
intptr gMemFree;                                             /* @801370ac 4B on PSX; callback pointer carrier */
int gMenuRotate[2];                                            /* @80051264 8B */
int gNumBanks;                                                 /* @801370b8 4B */
Group                  * gObjDefOffsetsGroup;                  /* @8013d4e0 4B */
Group * gPersistMidgroundObjInst;                              /* @8013d4c4 4B */
Group              * gPersistObjDef;                           /* @8013d4bc 4B */
Group * gPersistObjDefBoundingSpheres;                         /* @8013d4c8 4B */
Group              * gPersistObjInst;                          /* @8013d4c0 4B */
tSkid gPrevSkidSm[8][4];                                       /* @8011e2f0 896B */
Camera_tCamSlot gReplayCameraSlots[32];                        /* @8011dbdc 1024B */
int gSPCH_Initialized;                                         /* @801370b0 4B */
intptr gSampleRequest;                                       /* @80137094 4B on PSX; callback pointer */
int gSaveChunk[8][4];                                          /* @8011e770 128B */
Skidmark_Segment * gSaveSeg[8][4];                             /* @8011e6f0 128B */
intptr gSentenceRuleSet;                                     /* @8013709c 4B on PSX; callback pointer */
intptr gSentenceRuleTest;                                    /* @80137098 4B on PSX; callback pointer */
int gShowroomLights;                                           /* @800514b4 4B */
int gStatusSm[8][4];                                           /* @8011e670 128B */
int gSteerRatio;                                               /* @8013d2f8 4B */
int gTAddCSmoke;                                               /* @8013d4f4 4B */
int gTAddCarExtraSfx[8][4];                                    /* @8011e270 128B */
int gTAddCarSfx[8];                                            /* @8011e1d0 32B */
int gTAddCarWheelDelay;                                        /* @8013d4f0 4B */
int gTAddCarWheelSfx[8][4];                                    /* @8011e1f0 128B */
int gTEnviroEffect[8];                                         /* @8011e1b0 32B */
int gTMoveSouffle;                                             /* @8013d450 4B */
int gTotalMem;                                                 /* @8013d7c4 4B */
u_int gTotalMemory;                                            /* @8013dabc 4B */
intptr *gVoxBanks;                                           /* @801370b4 4B on PSX; bank-pointer array */
int gWindDir;                                                  /* @8013d454 4B */
int gZDepth;                                                   /* @8013db74 4B */
int g_currentthread;                                           /* @8013dd5c 4B */
int g_mdecdrawsyncfailed;                                      /* @80052b30 4B */
coorddef gravity_ch;                                           /* @801165d4 12B */
int gtrackNumber;                                              /* @8013d4dc 4B */
int leftMult;                                                  /* @8013d310 4B */
int libticks;                                                  /* @8013dcb0 4B */
int linkmodeflag;                                              /* @8013dd0c 4B */
void *(*loadfilecallback)(void *dest, char *name, int memclass); /* @8013dd60 pointer-return hook */
int mb_default;                                                /* @8013dcc8 4B */
int nomessage;                                                 /* @80051a78 4B */
int numValidCams;                                              /* @8013d3f0 4B */
unsigned int numjoy;                                           /* @8013dc84 4B */
int openkeys[32];                                              /* @801231fc 128B */
char * otbuf;                                                  /* @8013dd04 4B */
int powerControl;                                              /* @8013d320 4B */
matrixtdef prevCamMat[2];                                      /* @80123444 88B */
coorddef prevCamPos[2];                                        /* @8012342c 24B */
char * primbuf;                                                /* @8013dd08 4B */
int quitType;                                                  /* @8013d430 4B */
int rearMult;                                                  /* @8013d30c 4B */
int rightMult;                                                 /* @8013d314 4B */
int roadMult;                                                  /* @8013d304 4B */
tScreenCarSelectDuel * screenCarSelectDuel;                    /* @80052040 4B */
tScreenCarSelectTwoPlayer * screenCarSelectPlayerTwo;          /* @80052048 4B */
tScreenCarSelectTwoPlayer * screenCarSelectTwoPlayer;          /* @80052044 4B */
tScreenMain * screenMain;                                      /* @80051e58 8B */
tScreenMemcard * screenMemcard;                                /* @800528f0 4B */
tScreenPinkSlipsCarSelect * screenPinkSlipsCarSelectPlayerTwo; /* @80052050 8B */
tScreenPinkSlipsCarSelect * screenPinkSlipsCarSelectTwoPlayer; /* @8005204c 4B */
tScreenTrackRecords * screenTrackRecords;                      /* @800520d0 8B */
int screenbpp;                                                 /* @8013dc90 4B */
int screenheight;                                              /* @8013dc8c 4B */
int screenwidth;                                               /* @8013dc88 4B */
int showRoomFlag;                                              /* @80051260 4B */
cluttbl shpfontclut;                                           /* @8011fdb0 48B */
Sim_tSimGlobalVar simGlobal;                                   /* @8011e0ac 24B */
Sim_tSimSystemVar simVar;                                      /* @8011e0c4 28B */
int skipRender;                                                /* @8013d42c 4B */
char skip_all;                                                 /* @80052a2e 1B */
int slippery;                                                  /* @8013d318 4B */
int steeringControl;                                           /* @8013d31c 4B */
int ticks;                                                     /* @8013dcac 4B */
int timerflag;                                                 /* @8013dd4c 4B */
int timerhz;                                                   /* @8013dcc4 4B */
char titleScreenDisplayed;                                     /* @80052a70 1B */
int tmrsub[8];                                                 /* @8012360c 32B */
int totalAvailMem;                                             /* @8013d9dc 4B */
int unPauseDelay;                                              /* @8013d428 4B */
char uncompressed_data[32];                                    /* @8011dbbc 32B */
short user_exit;                                               /* @80052a2c 2B */

}

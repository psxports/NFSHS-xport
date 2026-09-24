/* link_trampolines.cpp -- AUTO-GENERATED flat->member bridges (LINK phase). */
#include "../nfs4_types.h"
#include <stddef.h>
#include <stdarg.h>

extern "C" tAllScreens* tAllScreens_ctor(tAllScreens* p) {
  return new((void*)p) tAllScreens();
}
extern "C" void tAllScreens_dtor(tAllScreens* p, int) {
  p->~tAllScreens();
}
extern "C" tFEApplication* tFEApplication_ctor(tFEApplication* p) {
  return new((void*)p) tFEApplication();
}
extern "C" void tFEApplication_dtor(tFEApplication* p, int) {
  p->~tFEApplication();
}
extern "C" tGlobalMenuDefs* tGlobalMenuDefs_ctor(tGlobalMenuDefs* p) {
  p->ConstructBody();
  return p;
}
extern "C" void tGlobalMenuDefs_dtor(tGlobalMenuDefs* p, int mode) {
  p->DestroyBody(mode);
}
extern "C" tMenuNFS4* tMenuNFS4_ctor(tMenuNFS4* p, u_int flags, tScreen* screen,
                           tMenu* next, tMenu* options,
                           void (*onPress)(tMenuCommand&), short title,
                           tMenuItem* first, ...) {
  new((void*)p) tMenuNFS4(flags, screen, next, options, onPress, title);
  tMenuItem* rest[64];
  int count = 0;
  va_list args;
  va_start(args, first);
  if (first) {
    do {
      rest[count] = va_arg(args, tMenuItem*);
    } while (rest[count++] && count < 64);
  } else {
    rest[0] = 0;
  }
  va_end(args);
  p->_base_tMenu.tMenuConstructor(first, rest);
  return p;
}

extern "C" void Display(tDialogBase* a0) {
  a0->Display();
}
extern "C" void Hide(tDialogBase* a0) {
  a0->Hide();
}
extern "C" short Run(tDialogInteractive* a0) {
  return (short)(a0->Run());
}
extern "C" void Redraw(tFEApplication* a0) {
  a0->Redraw();
}
void UpdateMusic(tFEApplication* a0) {
  a0->UpdateMusic();
}
void SaveTournament(tTournamentManager* a0, tSaveTournament* a1) {
  a0->SaveTournament(a1);
}
void LoadTournament(tTournamentManager* a0, tSaveTournament* a1) {
  a0->LoadTournament(a1);
}
void SaveTracks(tTrackManager* a0, tSaveTrackInfo* a1) {
  a0->SaveTracks(*a1);
}
void LoadTracks(tTrackManager* a0, tSaveTrackInfo* a1) {
  a0->LoadTracks(*a1);
}
void SaveCars(tCarManager* a0, tSaveCarInfo* a1) {
  a0->SaveCars(*a1);
}
void LoadCars(tCarManager* a0, tSaveCarInfo* a1, short a2) {
  a0->LoadCars(*a1, a2);
}
void LoadPinkSlipsCars(tCarManager* a0, tSaveCarInfo* a1, short a2) {
  a0->LoadPinkSlipsCars(*a1, a2);
}
int GetHelpText(tScreenControllerConfig* a0) {
  return (int)(a0->GetHelpText());
}
void DisplayHelp(tFEApplication * a0, int a1) {
  a0->DisplayHelp(a1);
}
void GetGarageCar(tCarManager* a0, unsigned a1, tCarInfo* a2, int a3) {
  a0->GetGarageCar(a1, *a2, a3);
}
void * GetCarFromID(tCarManager* a0, int a1) {
  return (void *)(a0->GetCarFromID(a1));
}
void * TransitionIsFinished(tOptionsMenu * a0) {
  return (void *)(a0->TransitionIsFinished());
}
int Percentage(tMenuItemLeftRightAudioSlider * a0) {
  return (int)(a0->Percentage());
}
void DrawBackgroundImage(tScreen* a0, int a1, int a2, tTexture_ShapeInfo* a3, int a4) {
  a0->DrawBackgroundImage(a1, a2, a3, a4);
}
extern "C" void * IsShapeFileLoaded(tScreen* a0, tShapeInformation* a1) {
  return (void *)(a0->IsShapeFileLoaded(*a1));
}
void FreeShapes(tScreen* a0, tShapeInformation* a1) {
  a0->FreeShapes(*a1);
}
void InitializeShapes(tScreen* a0, tShapeInformation* a1, int a2) {
  a0->InitializeShapes(*a1, a2);
}
void AsyncLoadSwapShapeFile(tScreen* a0, char* a1) {
  a0->AsyncLoadSwapShapeFile(a1);
}
void AsyncLoadShapeFile(tScreen* a0, char* a1, tShapeInformation* a2) {
  a0->AsyncLoadShapeFile(a1, *a2);
}
void TurnOn(tVideoWall* a0) {
  a0->TurnOn();
}
void TurnOff(tVideoWall* a0) {
  a0->TurnOff();
}
void TurnOffInstant(tVideoWall* a0) {
  a0->TurnOffInstant();
}
void UpdateImages(tVideoWall* a0) {
  a0->UpdateImages();
}
void UpdateTransition(tVideoWall* a0) {
  a0->UpdateTransition();
}
void Draw(tVideoWall* a0) {
  a0->Draw();
}
void SetAvailable(tVideoWall* a0, unsigned a1) {
  a0->SetAvailable(a1);
}
void SetAvailableText(tVideoWall* a0, short a1, short a2, short a3) {
  a0->SetAvailableText(a1, a2, a3);
}
void GetTrack(tTrackManager* a0, unsigned a1, void* a2) {
  a0->GetTrack(a1, *(tTrackInformation*)a2);
}
extern "C" tTrackInformation * GetTrackByID(tTrackManager* a0, short a1) {
  return (tTrackInformation *)(a0->GetTrackByID(a1));
}
void PreLoad(tScreen* a0) {
  a0->PreLoad();
}
tCarInfo * GetCarFromID(tCarManager * a0, short a1) {
  return (tCarInfo *)(a0->GetCarFromID(a1));
}
void GetGarageCar(tCarManager * a0, short a1, tCarInfo * a2, short a3) {
  a0->GetGarageCar(a1, *a2, a3);
}
extern "C" void GetPinkSlipsCar(tCarManager * a0, short a1, tCarInfo * a2, short a3) {
  a0->GetPinkSlipsCar(a1, *a2, a3);
}
extern "C" void GetAwardInformation(tTournamentManager * a0, tAwardInformation * a1) {
  a0->GetAwardInformation(a1);
}
short PlayerRanking(tTournamentManager * a0, short a1) {
  return (short)(a0->PlayerRanking(a1));
}
extern "C" void UploadSwapShapes(tScreen * a0, int a1) {
  a0->UploadSwapShapes(a1);
}
extern "C" void UploadShapes(tScreen* a0, tShapeInformation* a1, short a2, short a3, int a4, int a5) {
  a0->UploadShapes(*a1, a2, a3, a4, a5);
}
void InitializeShapes(tScreen* a0, tShapeInformation* a1, unsigned a2) {
  a0->InitializeShapes(*a1, a2);
}
void Init(tCreditManager* a0, u_long a1) {
  a0->Init(a1);
}
void DeInit(tCreditManager* a0) {
  a0->DeInit();
}
void Draw(tCreditManager* a0, int a1) {
  a0->Draw(a1);
}
short TextValue(tListIteratorTournament * a0, tPlayer a1) {
  return (short)(a0->TextValue(a1));
}
short * GetTrackList(tTournamentManager * a0, short a1, short a2) {
  return (short *)(a0->GetTrackList(a1, a2));
}
extern "C" void GetTrackToRace(tTournamentManager * a0, tTrackInfo * a1) {
  a0->GetTrackToRace(a1);
}
short TextValue(tListIteratorTrack * a0, tPlayer a1) {
  return (short)(a0->TextValue(a1));
}
extern "C" void Decrement(tListIteratorTrack * a0, tPlayer a1) {
  a0->Decrement(a1);
}
void Increment(tListIteratorTrack * a0, tPlayer a1) {
  a0->Increment(a1);
}
void GetTrack(tTrackManager * a0, u_short a1, tTrackInformation * a2) {
  a0->GetTrack(a1, *a2);
}
void SetAvailable(tVideoWall * a0, u_short a1) {
  a0->SetAvailable(a1);
}
void ProcessInput(tScreen * a0, tPlayer a1, tInputKeyType & a2, tMenuCommand & a3) {
  a0->ProcessInput(a1, a2, a3);
}
tCarInfo * GetCarFromSimID(tCarManager * a0, short a1) {
  return (tCarInfo *)(a0->GetCarFromSimID(a1));
}
extern "C" void tScreen_ctor(tScreen* a0) {
  new((void*)a0) tScreen();
}
void tScreen_dtor(tScreen* a0, int a1) {
  ((tScreen*)a0)->~tScreen();
}
void tDialogYesNo_ctor(tDialogYesNo* a0) {
  new((void*)a0) tDialogYesNo();
}
extern "C" void tListIterator_dtor(tListIterator* a0) {
  ((tListIterator*)a0)->~tListIterator();
}
void tScreen_dtor(tScreen* a0) {
  ((tScreen*)a0)->~tScreen();
}
extern "C" void tScreenCarSelect_ctor(tScreenCarSelect* a0) {
  new((void*)a0) tScreenCarSelect();
}
extern "C" void tScreenCarSelect_dtor(tScreenCarSelect* a0) {
  ((tScreenCarSelect*)a0)->~tScreenCarSelect();
}
void tScreenCarSelectTwoPlayer_dtor(tScreenCarSelectTwoPlayer* a0) {
  ((tScreenCarSelectTwoPlayer*)a0)->~tScreenCarSelectTwoPlayer();
}
void tScreenCarSelectDuel_dtor(tScreenCarSelectDuel* a0) {
  ((tScreenCarSelectDuel*)a0)->~tScreenCarSelectDuel();
}
void tScreenPinkSlipsCarSelect_dtor(tScreenPinkSlipsCarSelect* a0) {
  ((tScreenPinkSlipsCarSelect*)a0)->~tScreenPinkSlipsCarSelect();
}


/* Typed bridges for recovered calls that pass the C++ object explicitly */
void AddCarToIngameList(tCarManager *manager, tCarModels *model, char *color) {
  manager->AddCarToIngameList(*model, *color);
}
short AdvanceToNextTrack(tTournamentManager *manager) {
  return manager->AdvanceToNextTrack();
}
long CheapestCarStockPrice(tCarManager *manager) {
  return manager->CheapestCarStockPrice();
}
long CalcUsedPrice(tCarManager *manager, short garage) {
  return manager->CalcUsedPrice(garage);
}
int FindSimilarCar(tCarManager *manager, tCarModels *model, char *color,
                   short count, tCarModels *models) {
  return manager->FindSimilarCar(*model, *color, count, models);
}
short GetClassList(tCarManager *manager, unsigned int carClass, int count,
                   tCarModels *models) {
  return manager->GetClassList((tCarClassType)carClass, (short)count, models);
}
void GetGarageCar(tCarManager *manager, unsigned short garage, tCarInfo *info,
                  int player) {
  manager->GetGarageCar((short)garage, *info, (short)player);
}
void GetStockCar(tCarManager *manager, unsigned short car, tCarInfo *info) {
  manager->GetStockCar((short)car, *info);
}
short GetLastTrackRaced(tTournamentManager *manager) {
  return manager->GetLastTrackRaced();
}
short GetMissionStages(tMissionManager *manager, short tier, short mission,
                       tStageInfo **stages) {
  return manager->GetMissionStages(tier, mission, stages);
}
void GetMissionToRace(tMissionManager *manager, tMissionInfo **mission) {
  manager->GetMissionToRace(mission);
}
short GetNumOwnedCars(tCarManager *manager, short player) {
  return manager->GetNumOwnedCars(player);
}
short GetNumTourneyCars(tCarManager *manager, short player) {
  return manager->GetNumTourneyCars(player);
}
short GetNumPinkSlipsCars(tCarManager *manager, short player) {
  return manager->GetNumPinkSlipsCars(player);
}
void InitializeIngameCarList(tCarManager *manager) {
  manager->InitializeIngameCarList();
}
void *IsCarAnAddedModel(tCarManager *manager, tCarModels *model, char *color) {
  return manager->IsCarAnAddedModel(*model, *color);
}
void LoadDescription(tMissionManager *manager, bool pursuit) {
  manager->LoadDescription(pursuit);
}
tAppCommand RunFrontEnd(tFEApplication *application) {
  return application->RunFrontEnd();
}
tAppCommand RunPostGame(tFEApplication *application) {
  return application->RunPostGame();
}
void UpdateAwardInformation(tTournamentManager *manager) {
  manager->UpdateAwardInformation();
}
void UpdateCarLineup(tTournamentManager *manager) {
  manager->UpdateCarLineup();
}
short IsTournamentFinished(tTournamentManager *manager) {
  return manager->IsTournamentFinished();
}
long PurchaseCar(tCarManager *manager, short model, short color, short player) {
  return manager->PurchaseCar(model, color, player);
}
long PurchaseUpgrade(tCarManager *manager, short garage, short flags, short player) {
  return manager->PurchaseUpgrade(garage, flags, player);
}
void SetCarAvailable(tCarManager *manager, int model, bool available) {
  manager->SetCarAvailable((tCarModels)model, available);
}
void SetCarViewable(tCarManager *manager, int model, bool viewable) {
  manager->SetCarViewable((tCarModels)model, viewable);
}
void SetTrackAvailable(tTrackManager *manager, short track, bool available) {
  manager->SetTrackAvailable(track, available);
}
void SetClassAvailable(tTrackManager *manager, int trackClass,
                       bool available) {
  manager->SetClassAvailable((tTrackClassType)trackClass, available);
}
void SetDimensions(tMenuItemLeftRightSlider *item, short x, short y,
                   short width, short height) {
  item->SetDimensions(x, y, width, height);
}
void SetState(tScreenCarSelect *screen, int state) {
  screen->SetState(state);
}
void SwapBackground(tScreenMain *screen, int background) {
  screen->SwapBackground(background);
}
void SetAvailableIcon(tVideoWall *wall, short icon, short frames, short x,
                      short y, tTexture_ShapeInfo *images) {
  wall->SetAvailableIcon(icon, frames, x, y, images);
}
void SetOffset(tVideoWall *wall, short x, short y) {
  wall->SetOffset(x, y);
}
void SetValid(tVideoWall *wall, short valid) {
  wall->SetValid(valid);
}
void CalcTrackFinishDamageBill(tTournamentManager *manager, bool recalculate,
                               long *bill, long *bonus) {
  manager->CalcTrackFinishDamageBill(recalculate, bill, bonus);
}
void SavePinkSlipsCars(tCarManager *manager, tSaveCarInfo *save, short player) {
  manager->SavePinkSlipsCars(*save, player, -1);
}
void GetTrophyName(tTournamentManager *manager, tTourneyInfo *tournament,
                   tTrophySize size, char *buffer, int place) {
  manager->GetTrophyName(tournament, size, buffer, place);
}
void Initialize(tVideoWall *wall, tTVConfig *config, tTexture_ShapeInfo *shapes,
                short first, short count, short *ordering, short flipAxis) {
  wall->Initialize(config, shapes, first, count, ordering, flipAxis);
}
void SetMenu(tMenuItemSlidingMenu *item, short bothMenus, void *menu) {
  item->SetMenu(bothMenus != 0, (tInsideBoxMenu *)menu);
}
int tScreen_ProcessInput(tScreen *screen, tPlayer player, tInputKeyType &key,
                         tMenuCommand &command) {
  screen->ProcessInput(player, key, command);
  return 0;
}
void TransitionOff(tScreen *screen, tScreen_TransitionType type, tMenu *menu) {
  screen->TransitionOff(type, menu);
}
void TransitionOn(tScreen *screen, tScreen_TransitionType type, tMenu *menu) {
  screen->TransitionOn(type, menu);
}
short TextValue(tListIteratorCar *iterator, tPlayer player) {
  return iterator->TextValue(player);
}
int Debounce(void *menu) {
  return (int)(intptr)((tPMenu *)menu)->Debounce();
}
int IsEnabled(void *item) {
  return (int)(intptr)((tPMenuItem *)item)->IsEnabled();
}
int IsDisabled(void *item) {
  return (int)(intptr)((tPMenuItem *)item)->IsDisabled();
}
int ItemEnabledNum(void *menu, int item) {
  return ((tPMenu *)menu)->ItemEnabledNum(item);
}
int NumEnabledItems(void *menu) {
  return ((tPMenu *)menu)->NumEnabledItems();
}

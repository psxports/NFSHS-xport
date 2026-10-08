/* Read-only render-state telemetry for the isolated web diagnostic build */
#if defined(__EMSCRIPTEN__) && NFSHS_WEB_RENDER_PROBE
#include "../nfs4_types.h"
#include <emscripten.h>
#include <stdio.h>

extern Car_tObj *Cars_gHumanRaceCarList[9];
extern Car_tObj *Cars_gList[9];
extern int Cars_gNumCars;
extern Camera_tInfo Camera_gInfo[2];
extern dashhud_info DashHUD_gInfo;
extern "C" GameSetup_tData GameSetup_gData;
extern Transformer_zScene *R3DCar_LoadedScenePointer[2][50];
extern char R3DCar_ObjectVisible[57];
extern int BWorld_gChunkCount;
extern "C" u_char *&Render_gPacketPtr;

void NFSHS_WebRenderProbe(DRender_tView *view, int phase)
{
    static unsigned int serial;
    static u_char *before;
    if (phase == 0) {
        before = Render_gPacketPtr;
        return;
    }
    if ((++serial % 60) != 0 || view->player < 0 || view->player >= 2)
        return;
    Car_tObj *car = Cars_gHumanRaceCarList[view->player];
    if (!car)
        return;
    int type = car->render.currentCarType;
    unsigned int bank = (unsigned char)car->render.currentCountry >> 7;
    Transformer_zScene *scene = type >= 0 && type < 50 ? R3DCar_LoadedScenePointer[bank][type] : nullptr;
    int facets = 0;
    int visible = 0;
    if (scene) {
        for (int i = 0; i < 57; ++i) {
            if (scene->obj[i])
                facets += scene->obj[i]->numFacet;
            visible += R3DCar_ObjectVisible[i] != 0;
        }
    }
    char report[2048];
    int used = snprintf(report,sizeof(report),
        "{\"sample\":%u,\"player\":%d,\"type\":%d,\"scene\":%u,\"facets\":%d,\"visiblePartsLastCar\":%d,"
        "\"detail\":%d,\"inside\":%d,\"worldOtz\":%d,\"subOtz\":%d,\"subOtSize\":%d,\"sortFlag\":%d,"
        "\"carPacketsBytes\":%d,\"chunks\":%d,\"camera\":[%d,%d,%d],\"car\":[%d,%d,%d],",
        serial,view->player,type,(unsigned int)(uintptr_t)scene,facets,visible,
        car->render.detail,car->render.inside,car->render.world_otz,car->render.sub_otz,
        car->render.sub_otSize,car->render.sort_flag,(int)(Render_gPacketPtr-before),BWorld_gChunkCount,
        view->cview.translation.x,view->cview.translation.y,view->cview.translation.z,
        car->N.position.x,car->N.position.y,car->N.position.z);
    used += snprintf(report+used,sizeof(report)-used,
        "\"cameraMode\":%d,\"anchorIsPlayer\":%d,\"showHud\":%d,\"hudOptions\":[%d,%d,%d,%d],\"cars\":[",
        Camera_gInfo[view->player].mode,Camera_gInfo[view->player].anchor == &car->N,
        DashHUD_gInfo.showhud[view->player],GameSetup_gData.carInfo[view->player].HudTach,
        GameSetup_gData.carInfo[view->player].HudTime,GameSetup_gData.carInfo[view->player].HudLapnum,
        GameSetup_gData.carInfo[view->player].HudPosition);
    for (int i = 0; i < Cars_gNumCars && i < 9; ++i) {
        Car_tObj *item = Cars_gList[i];
        if (!item)
            continue;
        used += snprintf(report+used,sizeof(report)-used,
            "%s{\"index\":%d,\"detail\":%d,\"type\":%d,\"worldOtz\":%d,\"sortFlag\":%d}",
            i ? "," : "",i,item->render.detail,item->render.currentCarType,
            item->render.world_otz,item->render.sort_flag);
    }
    snprintf(report+used,sizeof(report)-used,"]}");
    EM_ASM({
        let output = document.getElementById('render-diagnostics');
        if (!output) {
            output = document.createElement('pre');
            output.id = 'render-diagnostics';
            output.hidden = true;
            document.body.appendChild(output);
        }
        output.textContent = UTF8ToString($0);
    },report);
}
#endif

#define SDL_MAIN_HANDLED

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include "game/constant.h"
#include "game/game_app.h"

GameApp* app = nullptr;

#ifdef __EMSCRIPTEN__
static void mainloop(void) /* this will run often, possibly at the monitor's refresh rate */
{
    if (!app->Running())
    {
        emscripten_cancel_main_loop(); /* this should "kill" the app. */
    }

    app->RunOnce();
}
#endif

int main(int, char**)
{
    app = new GameApp;

    Size wsize {
        WindowWidth,
        WindowHeight
    };

    app->Init(wsize);

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(mainloop, 0, 1);
#else
    app->Run();
#endif

    return 0;
}

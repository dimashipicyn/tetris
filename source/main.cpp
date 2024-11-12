#define SDL_MAIN_HANDLED
#include "game/game_app.h"

int main(int, char**)
{
    GameApp app;
    app.Init();
    app.Run();
    return 0;
}

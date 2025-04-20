#include "game/constant.h"
#define SDL_MAIN_HANDLED

#include "game/game_app.h"

int main(int, char**)
{
    GameApp app;

    Size wsize{
        WindowWidth,
        WindowHeight
    };

    app.Init(wsize);
    app.Run();

    return 0;
}

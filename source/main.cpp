#define SDL_MAIN_HANDLED

#include "game/game_app.h"
#include "game/board.h"

int main(int, char**)
{
    GameApp app;

    Size wsize{
        Width * CellSize,
        Height * CellSize
    };

    app.Init(wsize);
    app.Run();

    return 0;
}

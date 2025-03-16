#define SDL_MAIN_HANDLED

#include "game/game_app.h"
#include "game/board.h"

int main(int, char**)
{
    GameApp app;

    Size wsize{
        Board::Width * Board::CellSize,
        Board::Height * Board::CellSize
    };

    app.Init(wsize);
    app.Run();

    return 0;
}

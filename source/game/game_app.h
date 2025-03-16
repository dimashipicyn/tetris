#pragma once

#include "core/app.h"

#include "pentamino.h"
#include "board.h"

class GameApp : public App
{
private:
    void OnInit() override;
    void OnUpdate() override;
    void OnRender() override;

    Tetramino* pentamino {};
    Board* board{};
};
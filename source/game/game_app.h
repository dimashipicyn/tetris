#pragma once

#include "core/app.h"
#include "board.h"

class GameApp : public App
{
public:
    void OnInit() override;
    void OnUpdate() override;
    void OnRender() override;

    // Board* board{};
};
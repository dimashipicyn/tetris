#pragma once

#include "core/app.h"

#include "pentamino.h"

class GameApp : public App
{
private:
    void OnInit() override;
    void OnInput() override;
    void OnUpdate() override;
    void OnRender() override;

    Pentamino* pentamino {};
};
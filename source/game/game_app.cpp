#include "game_app.h"
#include "core/renderer.h"
#include "core/math/matrix.h"

void GameApp::OnInit()
{
    pentamino = new Tetramino(*this, {1, 1}, 0.5f, TetraminoType::S);
    board = new Board(*this);
}

void GameApp::OnUpdate()
{
    board->Update(*this);
    // pentamino->Update(*this);
}

void GameApp::OnRender()
{
    board->Draw(*this);
    // pentamino->Draw(*this);
}
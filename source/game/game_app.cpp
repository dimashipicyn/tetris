#include "game_app.h"
#include "core/renderer.h"
#include "core/math/matrix.h"

void GameApp::OnInit()
{
    pentamino = new Tetramino(*this, {0, 0}, 0.5f, TetraminoType::Z);
    board = new Board;
}

void GameApp::OnUpdate()
{
    pentamino->Update(*this);
}

void GameApp::OnRender()
{
    board->Draw(*this);
    pentamino->Draw(*this);
}
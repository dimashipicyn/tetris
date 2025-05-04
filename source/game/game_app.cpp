#include "game_app.h"

#include "core/font.h"

void GameApp::OnInit()
{
    board = new Board(*this);
}

void GameApp::OnUpdate()
{
    board->Update(*this);
}

void GameApp::OnRender()
{
    board->Draw(*this);
}
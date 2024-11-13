#include "game_app.h"

void GameApp::OnInit()
{
    pentamino = new Pentamino(Assets, N_Pentamino);
}

void GameApp::OnInput()
{
}

void GameApp::OnUpdate()
{
}

void GameApp::OnRender()
{
    pentamino->Draw(Renderer);
}
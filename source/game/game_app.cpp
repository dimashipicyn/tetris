#include "game_app.h"

void GameApp::OnInit()
{
    block = Assets->LoadTexture("assets/block.png");
    block.SetPos({ 100, 100 });
}

void GameApp::OnInput()
{
}

void GameApp::OnUpdate()
{
}

void GameApp::OnRender()
{
    block.Draw(Renderer);
}
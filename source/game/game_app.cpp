#include "game_app.h"
#include "core/provider.h"
#include "core/state.h"
#include "game_state.h"
#include "menu_state.h"
#include "state_id.h"

void GameApp::OnInit()
{
    // board = new Board(*this);
    Font font("fonts/minogram_6x10.xml");

    font.SetScale(2.0f);
    Ui->SetFont(font);

    StateManager->Register<MenuState>(StateId::Menu);
    StateManager->Register<GameState>(StateId::Play, *this);
    StateManager->Change(StateId::Menu);
}

void GameApp::OnUpdate()
{
    // board->Update(*this);
}

void GameApp::OnRender()
{
    // board->Draw(*this);
}
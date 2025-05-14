#include "game_state.h"
#include "board.h"
#include <SDL_scancode.h>

GameState::GameState(GameApp& /*app*/)
{
    // NewGame(app);
}

void GameState::Update(App& app)
{
    if (app.Input->IsKeyClicked(SDL_SCANCODE_ESCAPE))
    {
        app.StateManager->Pop();
    }

    m_board->Update((GameApp&)app);
}

void GameState::Draw(App& app)
{
    m_board->Draw((GameApp&)app);
}

void GameState::NewGame(GameApp& app)
{
    m_board = std::make_unique<Board>(app);
}

bool GameState::Played() const
{
    return !!m_board && !m_board->GameOver();
}
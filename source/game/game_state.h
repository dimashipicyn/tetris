#pragma once

#include "core/state.h"

#include <memory>

class GameApp;
class Board;

class GameState : public State
{
public:
    GameState(GameApp& app);
    void Update(App&) override;
    void Draw(App&) override;
    void NewGame(GameApp& app);
    bool Played() const;

private:
    std::unique_ptr<Board> m_board {};
};
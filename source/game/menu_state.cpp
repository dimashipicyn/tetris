#include "menu_state.h"

#include "constant.h"
#include "core/app.h"
#include "core/color.h"
#include "core/math/point.h"
#include "core/provider.h"
#include "core/state.h"
#include "core/ui.h"
#include "game_state.h"
#include "state_id.h"

void MenuState::Update(App& app)
{
    ProduceBackgroundCells(app);
    UpdateCells(app.DeltaTime);
    RemoveInvisibleCells();
}

void MenuState::Draw(App& app)
{
    DrawBackground(app);
    DrawUi(app);
}

void MenuState::DrawUi(App& app)
{
    Ui* ui = Provider::Self().Ui();
    StateManager* sm = Provider::Self().StateManager();

    const Point pos = { WindowWidth / 10, WindowHeight / 12 };
    const Size char_size = ui->GetFont().CalcTextSize("#");
    auto* play_state = sm->GetState<GameState>(StateId::Play);

    ui->Active(play_state->Played());
    if (ui->Button({ pos.x, pos.y + char_size.y * 2 }, "Resume"))
    {
        sm->Push(StateId::Play);
    }

    if (ui->Button({ pos.x, pos.y + char_size.y * 5 }, "Start game"))
    {
        play_state->NewGame((GameApp&)app);
        sm->Push(StateId::Play);
    }

    if (ui->Button({ pos.x, pos.y + char_size.y * 8 }, "Options"))
    {

    }

    if (ui->Button({ pos.x, pos.y + char_size.y * 11 }, "Exit"))
    {
        app.Stop();
    }
}

void MenuState::DrawBackground(App& app)
{
    for (Cell& cell : m_cell_queue)
    {
        cell.Draw(app);
    }
}

Point MenuState::GetRandStartPos() const
{
    const int x = m_dist(m_rd) / CellSize * CellSize;
    return {
        x,
        -CellSize
    };
}

void MenuState::ProduceBackgroundCells(App& app)
{
    m_produce_acc += app.DeltaTime;
    if (m_produce_acc > 0.5f)
    {
        m_produce_acc = 0;

        auto t = app.Assets->GetTexture("images/block.png", { CellSize, CellSize });
        m_cell_queue.push_front(Cell(t, Colors::Rand()));
        m_cell_queue.front().SetPos(GetRandStartPos());
    }
}

void MenuState::RemoveInvisibleCells()
{
    while (!m_cell_queue.empty())
    {
        if (m_cell_queue.back().GetPos().y > WindowHeight)
        {
            m_cell_queue.pop_back();
        }
        else
        {
            break;
        }
    }
}

void MenuState::UpdateCells(float dt)
{
    m_move_acc += dt * 50;
    if (m_move_acc >= 1.0f)
    {
        for (Cell& cell : m_cell_queue)
        {
            cell.SetPos(AddPoint(cell.GetPos(), { 0, (int)m_move_acc }));
        }
        m_move_acc = m_move_acc - (int)m_move_acc;
    }
}

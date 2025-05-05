#include "state.h"

#include "core/app.h"

StateManager::StateManager(App& app)
    : m_app(app)
{

}

void StateManager::Change(int state_id)
{
    if (!m_state_stack.empty())
    {
        m_state_stack.top()->OnEnd(m_app);
        m_state_stack.pop();
    }

    State* state = m_states[state_id].get();
    state->OnEnter(m_app);
    m_state_stack.push(state);
}

void StateManager::Push(int state_id)
{
    State* state = m_states[state_id].get();
    state->OnEnter(m_app);
    m_state_stack.push(state);
}

void StateManager::Pop()
{
    if (!m_state_stack.empty())
    {
        m_state_stack.top()->OnEnd(m_app);
        m_state_stack.pop();
    }
}

State* StateManager::CurrentState()
{
    if (!m_state_stack.empty())
    {
        return m_state_stack.top();
    }
    
    static State null_state;
    return &null_state;
}
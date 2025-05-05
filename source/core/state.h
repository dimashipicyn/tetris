#pragma once

#include <memory>
#include <stack>
#include <unordered_map>

class App;

class State
{
public:
    using Ptr = std::unique_ptr<State>;

    virtual ~State() = default;
    virtual void OnEnter(App&) {}
    virtual void Update(App&) {}
    virtual void Draw(App&) {}
    virtual void OnEnd(App&) {}

    template <class T, class... Args>
    static Ptr Create(Args... args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }
};

class StateManager
{
public:
    StateManager(App& app);

    template <class T, class... Args>
    void Register(int state_id, Args... args)
    {
        m_states[state_id] = State::Create<T>(std::forward<Args>(args)...);
    }

    void Change(int state_id);
    void Push(int state_id);
    void Pop();
    State* CurrentState();

private:
    std::unordered_map<int, State::Ptr> m_states {};
    std::stack<State*> m_state_stack {};

    App& m_app;
};
#pragma once

#include <memory>
#include <stack>
#include <unordered_map>
#include <utility>

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
    static Ptr Create(Args&&... args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }
};

class StateManager
{
public:
    StateManager(App& app);

    template <class T, class StateIdType, class... Args>
    void Register(StateIdType state_id, Args&&... args)
    {
        m_states[(int)state_id] = State::Create<T>(std::forward<Args>(args)...);
    }

    template<class StateIdType>
    void Change(StateIdType state_id)
    {
        Change((int)state_id);
    }

    template<class StateIdType>
    void Push(StateIdType state_id)
    {
        Push((int)state_id);
    }

    template<class T = State, class StateIdType>
    T* GetState(StateIdType state_id)
    {
        return static_cast<T*>(GetState((int)state_id));
    }

    void Pop();
    State* CurrentState();

private:
    void Change(int state_id);
    void Push(int state_id);
    State* GetState(int state_id);

    std::unordered_map<int, State::Ptr> m_states {};
    std::stack<State*> m_state_stack {};

    App& m_app;
};
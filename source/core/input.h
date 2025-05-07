#pragma once

#include <SDL.h>
#include <SDL_events.h>
#include <SDL_mouse.h>
#include <SDL_scancode.h>

#include "math/point.h"

enum class MouseButton
{
    Left,
    Middle,
    Right,

    Count
};

class Input
{
public:
    bool IsKeyDown(SDL_Scancode code)
    {
        return m_keyboard[code];
    }

    bool IsKeyClicked(SDL_Scancode code)
    {
        return !m_old_keyboard[code] && IsKeyDown(code);
    }

    bool IsExit() const
    {
        return m_exit;
    }

    const Point& MousePosition() const
    {
        return m_mouse_pos;
    }

    bool IsMouseDown(const MouseButton& button) const
    {
        return m_mouse_keys[button];
    }

    bool IsMouseClicked(const MouseButton& button) const
    {
        return !m_old_mouse_keys[button] && m_mouse_keys[button];
    }

private:
    friend class App;

    static constexpr const size_t MAX_KEYBOARD_KEYS = 350;

    void PollEvents()
    {
        m_old_keyboard = m_keyboard;
        m_old_mouse_keys = m_mouse_keys;

        auto mouse_ev = SDL_GetMouseState(&m_mouse_pos.x, &m_mouse_pos.y);
        m_mouse_keys[MouseButton::Left] = mouse_ev & SDL_BUTTON(SDL_BUTTON_LEFT);
        m_mouse_keys[MouseButton::Middle] = mouse_ev & SDL_BUTTON(SDL_BUTTON_MIDDLE);
        m_mouse_keys[MouseButton::Right] = mouse_ev & SDL_BUTTON(SDL_BUTTON_RIGHT);

        SDL_Event ev;
        while (SDL_PollEvent(&ev))
        {
            switch (ev.type)
            {
            case SDL_QUIT:
                m_exit = true;
                break;
            default:
                PollEvent(ev);
                break;
            }
        }
    }

    void PollEvent(const SDL_Event& event)
    {
        switch (event.type)
        {
        case SDL_KEYDOWN:
        {
            auto& key = event.key;
            if (key.repeat == 0 && key.keysym.scancode < MAX_KEYBOARD_KEYS)
            {
                m_keyboard[key.keysym.scancode] = true;
                m_last_key_pressed = key.keysym.scancode;
            }
            break;
        }
        case SDL_KEYUP:
        {
            auto& key = event.key;
            if (key.keysym.scancode < MAX_KEYBOARD_KEYS)
            {
                m_keyboard[key.keysym.scancode] = false;
                m_last_key_pressed = SDL_SCANCODE_UNKNOWN;
            }
            break;
        }
        }
    }

    struct Keyboard
    {
        bool& operator[](const SDL_Scancode& code)
        {
            return m_keys[code];
        }

        bool m_keys[MAX_KEYBOARD_KEYS] {};
    };

    Keyboard m_keyboard {};
    Keyboard m_old_keyboard {};

    SDL_Scancode m_last_key_pressed = SDL_SCANCODE_UNKNOWN;

    struct MouseKeys
    {
        bool& operator[](const MouseButton& code)
        {
            return m_keys[(size_t)code];
        }

        bool operator[](const MouseButton& code) const
        {
            return m_keys[(size_t)code];
        }

        bool m_keys[(size_t)MouseButton::Count] {};
    };

    Point m_mouse_pos {};
    MouseKeys m_mouse_keys {};
    MouseKeys m_old_mouse_keys {};

    bool m_exit = false;
};
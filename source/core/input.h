#pragma once

#include <SDL.h>
#include <SDL_events.h>
#include <SDL_scancode.h>

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

private:
    friend class App;

    static constexpr const size_t MAX_KEYBOARD_KEYS = 350;

    void PollEvents()
    {
        m_old_keyboard = m_keyboard;

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

        bool m_keys[MAX_KEYBOARD_KEYS]{};
    };

    Keyboard m_keyboard{};
    Keyboard m_old_keyboard{};

    SDL_Scancode m_last_key_pressed = SDL_SCANCODE_UNKNOWN;
    bool m_exit = false;
};
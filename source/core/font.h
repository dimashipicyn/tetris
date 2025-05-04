#pragma once

#include "math/point.h"
#include "math/size.h"

#include <memory>

class Font
{
public:
    Font();
    ~Font();
    Font(const char* font_path);
    void Load(const char* font_path);
    void Draw(const Point& pos, const char* fmt, ...) __attribute__((format(printf, 3, 4)));
    void SetScale(float scale);
    Size CalcTextSize(const char* fmt, ...) __attribute__((format(printf, 2, 3)));

private:
    struct Impl;
    std::unique_ptr<Impl> m_impl {};
};
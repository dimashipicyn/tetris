#pragma once

#include "aliases.h"
#include "renderer.h"

#include <memory>

class Object
{
public:
    virtual ~Object() = default;
    virtual void Update() = 0;
    virtual void Draw(Renderer* renderer) = 0;
};

using ObjectPtr = std::shared_ptr<Object>;

template<class T, class... Args>
using MakeObject = std::make_shared<T>(Args...&& args);
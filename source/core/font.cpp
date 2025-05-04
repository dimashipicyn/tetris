#include "font.h"

#include "assets.h"
#include "path_resolver.h"
#include "provider.h"

#include <cstdarg>
#include <cstdio>
#include <filesystem>
#include <memory>
#include <pugixml.hpp>
#include <unordered_map>

struct FontChar
{
    int x, y;
    int width, height;
    int xadvance;
    int yoffset;
};

struct FontData
{
    std::string textureFile;
    int lineHeight;
    std::unordered_map<int, FontChar> chars; // charID -> FontChar
};

class FontParser
{
public:
    static bool ParseFromXML(const char* xmlPath, FontData& outData)
    {
        auto path = ResolvePath(xmlPath);

        pugi::xml_document doc;
        if (!doc.load_file(path.c_str()))
        {
            SDL_Log("Load font '%s' failed\n", path.c_str());
            return false;
        }

        auto texture_path = std::filesystem::path(xmlPath).replace_extension(".png");
        outData.textureFile = texture_path.string();

        // Основные параметры шрифта
        outData.lineHeight = doc.child("font").child("common").attribute("lineHeight").as_int();

        // Парсим символы
        for (auto charNode : doc.child("font").child("chars").children("char"))
        {
            FontChar fc;
            fc.x = charNode.attribute("x").as_int();
            fc.y = charNode.attribute("y").as_int();
            fc.width = charNode.attribute("width").as_int();
            fc.height = charNode.attribute("height").as_int();
            fc.xadvance = charNode.attribute("xadvance").as_int();
            fc.yoffset = charNode.attribute("yoffset").as_int();

            outData.chars[charNode.attribute("id").as_int()] = fc;
        }

        return true;
    }
};

struct Font::Impl
{
    Texture texture;
    std::unordered_map<int, FontChar> chars {};
    float scale { 1.0f };
};

Font::Font() = default;

Font::~Font()
{
}

Font::Font(const char* font_path)
    : m_impl(std::make_unique<Impl>())
{
    Load(font_path);
}

void Font::Load(const char* font_path)
{
    if (!m_impl)
    {
        m_impl = std::make_unique<Impl>();
    }

    FontData data {};
    if (FontParser::ParseFromXML(font_path, data))
    {
        m_impl->texture = Provider::Self().Assets()->GetTexture(data.textureFile);
        m_impl->chars = std::move(data.chars);
    }
}

void Font::Draw(const Point& pos, const char* fmt, ...)
{
    static char buffer[BUFSIZ];

    va_list argptr;
    va_start(argptr, fmt);
    vsnprintf(buffer, BUFSIZ, fmt, argptr);
    va_end(argptr);

    int x = pos.x;
    int y = pos.y;
    const char* text = buffer;
    for (; *text; ++text)
    {
        auto it = m_impl->chars.find(*text);
        if (it == m_impl->chars.end())
            continue;

        const auto& fc = it->second;
        Rect srcRect = { fc.x, fc.y, fc.width, fc.height };
        Rect dstRect = { x, y + fc.yoffset, static_cast<int>(m_impl->scale * fc.width), static_cast<int>(m_impl->scale * fc.height) };
        Provider::Self().Renderer()->DrawTexture(m_impl->texture, srcRect, dstRect);
        x += (fc.xadvance * m_impl->scale);
    }
}

void Font::SetScale(float scale)
{
    m_impl->scale = scale;
}

Size Font::CalcTextSize(const char* fmt, ...)
{
    static char buffer[BUFSIZ];

    va_list argptr;
    va_start(argptr, fmt);
    vsnprintf(buffer, BUFSIZ, fmt, argptr);
    va_end(argptr);

    const char* text = buffer;
    Size result { 0, 0 };
    for (; *text; ++text)
    {
        auto it = m_impl->chars.find(*text);
        if (it == m_impl->chars.end())
            continue;

        const auto& fc = it->second;
        result.x += (fc.xadvance * m_impl->scale);
        result.y = std::max(result.y, fc.height);
    }
    return result;
}

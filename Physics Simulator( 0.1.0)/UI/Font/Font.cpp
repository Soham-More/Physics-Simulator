#include "Font.h"

UI::Font::Font()
{
    //ctor
}

UI::Font::~Font()
{
    //dtor
}

void UI::Font::Load(const std::string& FontPath)
{
    if(!font.loadFromFile(FontPath))
    {
        UI::ErrorStream::NewError("Error: Font Not Loaded", "Font at " + FontPath +
                                  " Could Not be loaded.\nPlease ensure that " + FontPath +
                                  " Exists and try again.", KILL_PROGRAM);
    }
}

sf::Font& UI::Font::GetFont()
{
    return font;
}

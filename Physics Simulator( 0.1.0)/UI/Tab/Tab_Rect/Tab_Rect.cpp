#include "Tab_Rect.h"

UI::Tab_Rect::Tab_Rect(sf::Vector2f Pos, std::string Text, UI::EventData& ev)
 : isClicked(false)
{
    Create(Pos, Text, ev);
}


void UI::Tab_Rect::Create(sf::Vector2f Pos, std::string Text, UI::EventData& ev)
{
    sf::Vector2f Size;

    Txt.setPosition(sf::Vector2f());
    Txt.setFont(UI::Init::Static_Font.GetFont());
    Txt.setString(Text);
    Txt.setColor(sf::Color::Black);
    Txt.scale(sf::Vector2f(1.0f, 25.0f / Txt.getGlobalBounds().height));
    Txt.setOrigin(sf::Vector2f(Txt.getGlobalBounds().width/2.0f, Txt.getGlobalBounds().height/2.0f));

    Size = sf::Vector2f(Txt.getGlobalBounds().width + 20.0f, 30.0f);

    Txt.setPosition(Pos + sf::Vector2f(Size.x / 2.0f, (Size.y - Txt.getGlobalBounds().height)));

    Box.setSize(Size);
    Box.setPosition(Pos);
    Box.setFillColor(sf::Color::White);

    this->Event = &ev;

    Sz = Size;
}

UI::Tab_Rect::~Tab_Rect()
{
    //dtor
}

bool UI::Tab_Rect::Draw(sf::RenderWindow& win)
{
    UI::MouseData ms = Event->MouseState;

    sf::FloatRect box(Box.getPosition(), Box.getSize());

    if(box.contains(ms.MousePos) && ms.LeftClick && !ms.Dragged)
    {
        isClicked = true;
        Box.setOutlineThickness(2);
        Box.setOutlineColor(sf::Color::Black);
    }
    else if(ms.LeftClick)
    {
        isClicked = false;
        Box.setOutlineThickness(0);
    }

    win.draw(Box);
    win.draw(Txt);

    return isClicked;
}

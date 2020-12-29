#include "Switch.h"

UI::Switch::Switch(sf::Vector2f Pos, sf::Color Switch_Color)
{
    this->Create(Pos, Switch_Color);
}

void UI::Switch::Create(sf::Vector2f Pos, sf::Color Switch_Color)
{
    sf::Vector2f Size(25, 12);

    Switch_Rect.setPosition(Pos);
    Switch_Rect.setSize(Size);

    ;
}

UI::Switch::~Switch()
{
    //dtor
}

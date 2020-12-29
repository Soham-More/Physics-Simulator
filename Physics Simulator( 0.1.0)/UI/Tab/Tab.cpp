#include "Tab.h"

UI::Tab::Tab(sf::Vector2f Pos, UI::EventData& ev)
{
    this->Pos = Pos;
    this->LPos = Pos;
    this->Event = &ev;
}

UI::Tab::~Tab()
{
    //dtor
}

int UI::Tab::Add_New_Tab(std::string Name)
{
    UI::Tab_Rect tr(LPos, Name, *Event);

    LPos += sf::Vector2f(tr.Get_Size().x + 2.0f, 0);

    tabs.push_back(tr);

    return tabs.size() - 1;
}

int UI::Tab::Draw(sf::RenderWindow& win)
{
    int i = 0;

    for(UI::Tab_Rect& tr : tabs)
    {
        if(tr.Draw(win))
        {
            Curr = i;
        }

        i++;
    }

    return Curr;
}

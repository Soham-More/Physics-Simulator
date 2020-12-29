#include "Slider.h"

#include<sstream>
std::string UI::Slider::float_to_string(float a)
{
    std::stringstream fss;

    fss << a;

    std::string ans = fss.str();

    return ans;
}

UI::Slider::Slider(sf::Vector2f Pos, float Size, UI::EventData& e, sf::Color Knob_Color) : isClicked(false)
{
    this->Create(Pos, Size, e, Knob_Color);
}

UI::Slider::~Slider()
{
    //dtor
}

void UI::Slider::Create(sf::Vector2f Pos, float Size, UI::EventData& e, sf::Color Knob_Color)
{
    float Knob_Size = 20;

    Knob.setSize(sf::Vector2f(Knob_Size + 5, Knob_Size));
    Knob.setOrigin(sf::Vector2f((Knob_Size + 5)/2, Knob_Size/2));
    Knob.setPosition(Pos + sf::Vector2f((Knob_Size + 5)/2, Knob_Size/2));
    Knob.setFillColor(Knob_Color);

    Holder.setSize(sf::Vector2f(Size, 2));
    Holder.setOrigin(sf::Vector2f(0, 1));
    Holder.setPosition(Pos + sf::Vector2f(0, Knob_Size/2));
    Holder.setFillColor(sf::Color::Black);

    Min_X = Pos.x;
    Max_X = Pos.x + Size;

    Event = &e;

    this->Pos = Pos;

    Set_Limits(Min, Max);
}

void UI::Slider::Set_Limits(float Min, float Max, float Init_Val)
{
    this->Min = Min;
    this->Max = Max;
    this->Value = Init_Val;

    float Size = Holder.getSize().x; /// Gets the Size of Slider
    float Number_Density = Size / (Max - Min); /// Calculates the Number Density( i.e Pixels per Number.)
    float Offset_X = Value * Number_Density;
    float X = Offset_X + Min_X;

    Holder.setPosition(sf::Vector2f(Holder.getPosition().x, (Min_Text.getGlobalBounds().height/2.0f) + Pos.y));
    Knob.setPosition(sf::Vector2f(Knob.getPosition().x, (Min_Text.getGlobalBounds().height/2.0f) + Pos.y));

    Knob.setPosition(sf::Vector2f(X, Knob.getPosition().y));

    Value_Txt.setFont(UI::Init::Static_Font.GetFont());

    Min_Text.setFont(UI::Init::Static_Font.GetFont());
    Min_Text.setString(UI::DataTypes::ConvertToString((int)Min));
    Min_Text.setCharacterSize(20);

    sf::FloatRect Txt_Rect = Min_Text.getGlobalBounds();

    Min_Text.setOrigin(Txt_Rect.width/2, Txt_Rect.height/2);
    Min_Text.setPosition(Pos);
    Min_Text.setFillColor(sf::Color::Black);

    Holder.move(Txt_Rect.width/2 + 10, 0);
    Knob.move(Txt_Rect.width/2 + 10, 0);

    Max_X -= Min_X;
    Min_X = Holder.getPosition().x;
    Max_X += Min_X;

    Max_Text.setFont(UI::Init::Static_Font.GetFont());
    Max_Text.setString(UI::DataTypes::ConvertToString((int)Max));

    Max_Text.setCharacterSize(20);
    Max_Text.setOrigin(0, Txt_Rect.height/2);
    Max_Text.setPosition(sf::Vector2f(Max_X + 15, Pos.y));
    Max_Text.setFillColor(sf::Color::Black);
}

void UI::Slider::Draw(sf::RenderWindow& win, bool ShowLimits)
{
    UI::MouseData ms = Event->MouseState;

    sf::FloatRect box();

    float New_X = ms.MousePos.x;

    if(New_X > Max_X) New_X = Max_X;
    else if(New_X < Min_X) New_X = Min_X;

    if(PointInRect(Knob, ms.MousePos) && ms.LeftClick && !ms.Dragged)
    {
        isClicked = true;
        Knob.setOutlineThickness(2);
        Knob.setOutlineColor(sf::Color::Black);

        Knob.setPosition(sf::Vector2f(New_X, Knob.getPosition().y));
    }
    else if(isClicked && ms.Dragged)
    {
        Knob.setPosition(sf::Vector2f(New_X, Knob.getPosition().y));
        isClicked = true;
    }
    else if(!PointInRect(Knob, ms.MousePos))
    {
        isClicked = false;
        Knob.setOutlineThickness(0);
    }

    if(isClicked)
    {
        float X = Knob.getPosition().x;
        float Size = Holder.getSize().x; /// Gets the Size of Slider
        float Offset_X = X - Min_X; /// Gets the no. of Pixels covered by Slider
        float Number_Density = Size / (Max - Min); /// Calculates the Number Density( i.e Pixels per Number.
        Value = Offset_X * (1/Number_Density); /// Get the Number Corresponding to That Pixel
    }

    if(isClicked)
    {
        Value_Txt.setString(float_to_string(Value));
        Value_Txt.setCharacterSize(15);
        sf::FloatRect infr = Value_Txt.getGlobalBounds();

        ValueBox.setSize(sf::Vector2f(infr.width + 10.0f, infr.height + 5.0f));
        ValueBox.setOrigin(ValueBox.getSize() * 0.5f);
        ValueBox.setPosition(Knob.getPosition() - sf::Vector2f(0, 30.0f));
        ValueBox.setFillColor(sf::Color(Knob.getFillColor().r, Knob.getFillColor().g, Knob.getFillColor().b, 192));
        ValueBox.setOutlineColor(sf::Color(255, 255, 255, 128));
        ValueBox.setOutlineThickness(1);

        Value_Txt.setPosition(ValueBox.getPosition() - sf::Vector2f((infr.width / 2.0f) + 1.25f, (infr.height / 2.0f) + 5.0f));
        Value_Txt.setFillColor(sf::Color(0, 0, 0, 200));

        win.draw(ValueBox);
        win.draw(Value_Txt);
    }

    win.draw(Holder);
    win.draw(Knob);

    win.draw(Min_Text);
    win.draw(Max_Text);
}

bool UI::Slider::PointInRect(sf::RectangleShape& r, sf::Vector2f p)
{
    sf::Vector2f Top_Left = r.getPosition() - r.getOrigin();
    sf::Vector2f Bottom_Right = r.getPosition() - r.getOrigin() + r.getSize();

    sf::Vector2f Point = p;

    return (Top_Left.x <= p.x && Top_Left.y <= p.y && Bottom_Right.x >= p.x && Bottom_Right.y >= p.y);
}

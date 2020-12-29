#include "Button.h"

UI::Button::Button() : isClicked(false)
{
    if(!sh.loadFromFile("PostFragment.vert", sf::Shader::Fragment))
    {
        UI::ErrorStream::NewError("File not Found!",
                                  "PostFragment.vert was not found!",
                                  KILL_PROGRAM);
    }
    if(!sh1.loadFromFile("Button_Shader.vert", sf::Shader::Fragment))
    {
        UI::ErrorStream::NewError("File not Found!",
                                  "Button_Shader.vert was not found!",
                                  KILL_PROGRAM);
    }
}

UI::Button::Button(sf::Vector2f Pos, sf::Vector2f Size, std::string Text, EventData& Event, sf::Color color, bool Reverse)
{
    isClicked = false;
    Create(Pos, Size, Text, Event, color, Reverse);
}

void UI::Button::Create(sf::Vector2f Pos, sf::Vector2f Size, std::string Text, EventData& Event, sf::Color color, bool Reverse)
{
    Box.setSize(Size * 0.9f);
    Box.setPosition(Pos + (Size * 0.05f));
    Box.setFillColor(color);

    ButtonSize = Size;
    ButtonPos = Pos;

    Txt.setPosition(sf::Vector2f());
    Txt.setFont(UI::Init::Static_Font.GetFont());
    Txt.setString(Text);
    Txt.setColor(sf::Color::Black);
    Txt.scale(sf::Vector2f(1.25f, 1.25f));
    Txt.setOrigin(sf::Vector2f(Txt.getGlobalBounds().width, Txt.getGlobalBounds().height) * 0.5f);
    Txt.rotate(90.0f * int(Reverse));

    isReversed = Reverse;

    this->Event = &Event;
}

void UI::Button::SetText(std::string title)
{
    Txt = sf::Text();

    Txt.setPosition(sf::Vector2f());
    Txt.setFont(UI::Init::Static_Font.GetFont());
    Txt.setString(title);
    Txt.setColor(sf::Color::Black);
    Txt.scale(sf::Vector2f(1.25f, 1.25f));
    Txt.setOrigin(sf::Vector2f(Txt.getGlobalBounds().width, Txt.getGlobalBounds().height) * 0.5f);
    Txt.rotate(90.0f * int(isReversed));
}

UI::Button::~Button()
{
    //dtor
}

bool UI::Button::Draw(sf::RenderWindow& win)
{
    sf::Vector2f MousePos = win.mapPixelToCoords(sf::Mouse::getPosition(win));

    isClicked = false;

    UI::MouseData ms = Event->MouseState;

    sf::FloatRect box(Box.getPosition(), Box.getSize());

    if(box.contains(MousePos))
    {
        Box.setSize(ButtonSize);
        Box.setPosition(ButtonPos);
    }
    else
    {
        Box.setSize(ButtonSize * 0.9f);
        Box.setPosition(ButtonPos + (ButtonSize * 0.05f));
    }

    if(box.contains(MousePos) && ms.LeftClick && !ms.Dragged)
    {
        isClicked = true;
        Box.setSize(ButtonSize * 0.9f);
        Box.setPosition(ButtonPos + (ButtonSize * 0.05f));
    }
    else if(ms.LeftClick)
    {
        isClicked = false;
    }

    sf::RectangleShape rect = Box;
    rect.setOutlineThickness(0);
    rect.setPosition(rect.getPosition() - sf::Vector2f(3, 3));
    rect.setSize(rect.getSize() + sf::Vector2f(6, 6));

    MousePos = win.mapPixelToCoords(sf::Mouse::getPosition(win), win.getDefaultView());

    sh1.setUniform("Mouse", sf::Vector2f(MousePos.x, 375.0f - MousePos.y));
    sh1.setUniform("Color", sf::Vector3f(0.0f, 0.0f, 0.0f));
    sh1.setUniform("Max", sf::Vector3f(1.0f, 1.0f, 1.0f));
    sh1.setUniform("val", 100.0f);
    sh1.setParameter("texture", sf::Shader::CurrentTexture);

    sh.setUniform("Mouse", sf::Vector2f(MousePos.x, 375.0f - MousePos.y));
    sh.setUniform("Max", sf::Vector3f(1.0f, 0.0f, 0.0f));
    sh.setUniform("val", 50.0f);

    Box.setFillColor(sf::Color::Cyan);

    sf::FloatRect tfr = Txt.getGlobalBounds();

    if(isReversed)
    {
        Txt.setPosition(Box.getPosition() + ((Box.getSize() + sf::Vector2f(30.0f, 0.0f)) * 0.5f));
    }
    else
    {
        Txt.setPosition(Box.getPosition() + ((Box.getSize() - sf::Vector2f(0.0f, 30.0f)) * 0.5f));
    }

    sf::RenderStates rs;
    rs.shader = &sh;

    sf::RenderStates rs1;
    rs1.shader = &sh1;

    win.draw(rect, rs);
    win.draw(Box);

    win.draw(Txt, rs1);

    return isClicked;
}

#include "Textbox.h"

UI::Textbox::Textbox(sf::Vector2f Pos, int Sz, EventData& Event, const std::string& InitText, bool OnlyNum)
{
    Create(Pos, Sz, Event, InitText, OnlyNum);
}

UI::Textbox::~Textbox()
{
    //dtor
}

void UI::Textbox::Create(sf::Vector2f Pos, int Sz, EventData& Event, const std::string& InitText, bool OnlyNum)
{
    float y = 30.0f;

    Box.setPosition(Pos);
    Box.setSize(sf::Vector2f(Sz, y));
    Box.setFillColor(TextBoxStyle.Default_Color);
    Box.setOutlineColor(sf::Color::Blue);
    Box.setOutlineThickness(0);

    line.setSize(sf::Vector2f(2.0f, y - 5.0f));
    line.setPosition(Pos + sf::Vector2f(5.0f, 2.5f));
    line.setFillColor(sf::Color::Black);

    txt.setFont(UI::Init::Static_Font.GetFont());
    txt.setPosition(Pos - sf::Vector2f(-2.0f, 5.0f));
    txt.setColor(sf::Color::Black);
    txt.setString(InitText);
    Text = InitText;

    for(char i : InitText)
    {
        if(i == '.')
        {
            isDotPresent = true;
        }
        if(i == '-')
        {
            isNegative = true;
        }
    }

    OnlyN = OnlyNum;

    Position = Text.size();

    this->Event = &Event;
}

void UI::Textbox::SetStyle(TextBox_Style& ts)
{
    TextBoxStyle = ts;

    txt.scale(TextBoxStyle.Scale);
    Box.scale(TextBoxStyle.Scale);
    line.scale(TextBoxStyle.Scale);

    txt.setFillColor(TextBoxStyle.Text_Color);
    Box.setFillColor(TextBoxStyle.Default_Color);

    if(TextBoxStyle.isCentered)
    {
        sf::Vector2f Size = Box.getSize();
        sf::Vector2f Pos = Box.getPosition();

        sf::FloatRect tfr = txt.getGlobalBounds();

        txt.setPosition(Pos + sf::Vector2f(tfr.width / 2.0f, 0.0f) - sf::Vector2f(-2.0f, 5.0f));
    }
}

void UI::Textbox::Update()
{
    UI::MouseData& ms = Event->MouseState;

    UI::Graphics::Console.SetEventHandler(*Event);

    if(PointInRect(Box, ms.MousePos) && ms.LeftClick && !ms.Dragged)
    {
        if(isClicked)
        {
            DClick = true;
        }
        isClicked = true;

        Box.setFillColor(TextBoxStyle.Selected_Color);
        Box.setOutlineThickness(2);
    }
    else if(isClicked && ms.Dragged)
    {
        DClick = false;
        isClicked = true;

        Box.setFillColor(TextBoxStyle.Selected_Color);
        Box.setOutlineThickness(2);
    }
    else if(!PointInRect(Box, ms.MousePos) && ms.LeftClick)
    {
        DClick = false;
        isClicked = false;

        Box.setFillColor(TextBoxStyle.Default_Color);
        Box.setOutlineThickness(0);
    }

    if(isClicked && sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        DClick = false;
        isClicked = false;

        Box.setFillColor(TextBoxStyle.Default_Color);
        Box.setOutlineThickness(0);
    }

    if(isClicked)
    {
        char a = UI::Graphics::Console.Listen_Charecter();

        if(!(sf::Keyboard::isKeyPressed(sf::Keyboard::RShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) && isalpha(a))
        {
            a = a + 32;
        }

        if(DClick)
        {
            Position = GetCursorPosition();
            DClick = false;
        }

        if(int(a))
        {
            if(!OnlyN)
            {
                std::string temp = Text;
                temp.insert(Position, 1, a);

                txt.setString(temp);

                float TXpos = txt.getGlobalBounds().width + txt.getGlobalBounds().left;
                float BXpos = Box.getGlobalBounds().width + Box.getGlobalBounds().left;

                if(TXpos < (BXpos - 10.0f))
                {
                    Text = temp;
                    Position++;
                }
                else
                {
                    txt.setString(Text);
                }

                isValueChanged = true;
            }
            else
            {
                if(isdigit(a) || ((a == '.') && !isDotPresent) || ((a == '-') && !isNegative && (Position == 0)))
                {
                    std::string temp = Text;
                    temp.insert(Position, 1, a);

                    txt.setString(temp);

                    float TXpos = txt.getGlobalBounds().width + txt.getGlobalBounds().left;
                    float BXpos = Box.getGlobalBounds().width + Box.getGlobalBounds().left;

                    if(TXpos < (BXpos - 0.0f))
                    {
                        Text = temp;
                        Position++;
                    }
                    else
                    {
                        txt.setString(Text);
                    }

                    if(a == '.')
                    {
                        isDotPresent = true;
                    }
                    if(a == '-')
                    {
                        isNegative = true;
                    }

                    isValueChanged = true;
                }
            }

            LMoved = false;
            RMoved = false;
            Backspaced = false;
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace))
        {
            if(bs_clk.getElapsedTime().asSeconds() >= W_t_bs && (Position - 1) >= 0)
            {
                if(Text[Position - 1] == '.')
                {
                    isDotPresent = false;
                }
                else if(Text[Position - 1] == '-')
                {
                    isNegative = false;
                }

                Text.erase(Position - 1, 1);

                Position--;

                bs_clk.restart();
                if(Backspaced)
                {
                    W_t_bs *= 0.95f;
                }

                isValueChanged = true;
            }

            LMoved = false;
            RMoved = false;
            Backspaced = true;
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            if(lm_clk.getElapsedTime().asSeconds() >= W_t_ML && (Position - 1) >= 0)
            {
                Position--;

                lm_clk.restart();
                if(LMoved)
                {
                    W_t_ML *= 0.95f;
                }
            }

            LMoved = true;
            RMoved = false;
            Backspaced = false;
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            if(rm_clk.getElapsedTime().asSeconds() >= W_t_MR && (Position + 1) <= Text.size())
            {
                Position++;

                rm_clk.restart();
                if(RMoved)
                {
                    W_t_MR *= 0.95f;
                }
            }

            LMoved = false;
            RMoved = true;
            Backspaced = false;
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Home))
        {
            Position = 0;

            LMoved = false;
            RMoved = false;
            Backspaced = false;
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::End))
        {
            Position = Text.size();

            LMoved = false;
            RMoved = false;
            Backspaced = false;
        }
        else
        {
            LMoved = false;
            RMoved = false;
            Backspaced = false;
        }

        if(!Backspaced) W_t_bs = 0.25f;
    }

    txt.setString(Text);

    if(TextBoxStyle.isCentered)
    {
        float Size = Box.getGlobalBounds().width;
        sf::Vector2f Pos = Box.getPosition();

        float tfr = txt.findCharacterPos(Text.size()).x - txt.getGlobalBounds().left;

        txt.setPosition(Pos + sf::Vector2f((Size - tfr) / 2.0f, 0.0f) - sf::Vector2f(-2.0f, 5.0f));
    }

    sf::Vector2f Pos = sf::Vector2f(txt.findCharacterPos(Position).x + 0.0f,
                                    Box.getPosition().y + 2.5f);

    line.setPosition(Pos);
}

void UI::Textbox::Draw(sf::RenderWindow& win)
{
    win.draw(Box);

    if(TextBoxStyle.Bold_Text)
    {
        txt.setFillColor(sf::Color::Black);
        win.draw(txt);
        txt.setFillColor(sf::Color(TextBoxStyle.Text_Color.r, TextBoxStyle.Text_Color.g, TextBoxStyle.Text_Color.b, 192));
        win.draw(txt);
    }
    else
    {
        win.draw(txt);
    }

    if(Show && isClicked) win.draw(line);

    if(blk.getElapsedTime().asSeconds() >= 0.5f)
    {
        Show = !Show;

        blk.restart();
    }
}

int UI::Textbox::GetCursorPosition()
{
    UI::MouseData ms = UI::Graphics::Console.GetEventHandler()->MouseState;

    int N_pos = 0;
    float N_dist = 0;

    for(int i = 0; i <= Text.size(); i++)
    {
        float dy = std::abs(txt.findCharacterPos(i).x - ms.MousePos.x);

        if(i == 0)
        {
            N_dist = dy;
        }
        else if(N_dist > dy)
        {
            N_pos = i;
            N_dist = dy;
        }
    }

    return N_pos;
}

void UI::Textbox::resetValue(std::string val)
{
    isDotPresent = false;
    isNegative = false;
    isValueChanged = false;

    for(char i : val)
    {
        if(i == '.')
        {
            isDotPresent = true;
        }
        if(i == '-')
        {
            isNegative = true;
        }
    }

    Text = val;
    txt.setString(val);
    Position = val.size();
}

bool UI::Textbox::PointInRect(sf::RectangleShape& r, sf::Vector2f p)
{
    sf::Vector2f Top_Left = r.getPosition() - r.getOrigin();
    sf::Vector2f Bottom_Right = r.getPosition() - r.getOrigin() + r.getSize();

    sf::Vector2f Point = p;

    return (Top_Left.x <= p.x && Top_Left.y <= p.y && Bottom_Right.x >= p.x && Bottom_Right.y >= p.y);
}

#include "Object_Editor.h"
#include<sstream>

std::string float_to_string(float a)
{
    std::stringstream fss;

    fss << a;

    std::string ans = fss.str();

    std::string result;

    bool Decimal_Encountered = false;

    int Places_After_Decimal = 0;

    for(char c : ans)
    {
        if(c == '.')
        {
            Decimal_Encountered = true;
        }

        result += c;

        if(Places_After_Decimal >= 2)
        {
            if(result == "-0.00") result = 0.0f;

            return result;
        }

        if(Decimal_Encountered)
        {
            Places_After_Decimal++;
        }
    }

    return ans;
}

Object_Editor::Object_Editor()
{
    Pos_Label.setFont(UI::Init::Static_Font.GetFont());
    x.setFont(UI::Init::Static_Font.GetFont());
    y.setFont(UI::Init::Static_Font.GetFont());
    z.setFont(UI::Init::Static_Font.GetFont());

    radius.setFont(UI::Init::Static_Font.GetFont());

    Color_Label.setFont(UI::Init::Static_Font.GetFont());
    pv.setFont(UI::Init::Static_Font.GetFont());
    r.setFont(UI::Init::Static_Font.GetFont());
    g.setFont(UI::Init::Static_Font.GetFont());
    b.setFont(UI::Init::Static_Font.GetFont());


    v_Label.setFont(UI::Init::Static_Font.GetFont());
    vx.setFont(UI::Init::Static_Font.GetFont());
    vy.setFont(UI::Init::Static_Font.GetFont());
    vz.setFont(UI::Init::Static_Font.GetFont());

    a_Label.setFont(UI::Init::Static_Font.GetFont());
    ax.setFont(UI::Init::Static_Font.GetFont()); avx.setFont(UI::Init::Static_Font.GetFont());
    ay.setFont(UI::Init::Static_Font.GetFont()); avy.setFont(UI::Init::Static_Font.GetFont());
    az.setFont(UI::Init::Static_Font.GetFont()); avz.setFont(UI::Init::Static_Font.GetFont());

    B.setFont(UI::Init::Static_Font.GetFont());
    Bx.setFont(UI::Init::Static_Font.GetFont());
    By.setFont(UI::Init::Static_Font.GetFont());
    Bz.setFont(UI::Init::Static_Font.GetFont());

    G.setFont(UI::Init::Static_Font.GetFont());
    Gx.setFont(UI::Init::Static_Font.GetFont());
    Gy.setFont(UI::Init::Static_Font.GetFont());
    Gz.setFont(UI::Init::Static_Font.GetFont());

    C.setFont(UI::Init::Static_Font.GetFont());
    Cx.setFont(UI::Init::Static_Font.GetFont());
    Cy.setFont(UI::Init::Static_Font.GetFont());
    Cz.setFont(UI::Init::Static_Font.GetFont());

    ab_Label.setFont(UI::Init::Static_Font.GetFont());
    abx.setFont(UI::Init::Static_Font.GetFont()); avx.setFont(UI::Init::Static_Font.GetFont());
    aby.setFont(UI::Init::Static_Font.GetFont()); avy.setFont(UI::Init::Static_Font.GetFont());
    abz.setFont(UI::Init::Static_Font.GetFont()); avz.setFont(UI::Init::Static_Font.GetFont());

    m_Label.setFont(UI::Init::Static_Font.GetFont());
    c_Label.setFont(UI::Init::Static_Font.GetFont());

    if(!Show_More_Tex.loadFromFile("Textures/Arrow.png"))
    {
        UI::ErrorStream::NewError("File not Found!",
                                  "Arrow.png was not found in Textures folder!",
                                  KILL_PROGRAM);
    }
}

void Object_Editor::Create(int ID)
{
    id = ID;
    Offset_Pos = (float(id - 1) * sf::Vector2f(500, 0)) + sf::Vector2f(53.0f, 0.0f);
}

void Object_Editor::Set(PE::System_Properties* p, UI::EventData* ed)
{
    sysp = p;
    evtd = ed;

    UI::TextBox_Style ts;

    ts.isCentered = true;
    ts.Selected_Color = sf::Color(255, 255, 255, 128);
    ts.Default_Color = sf::Color(255, 255, 255, 0);

    title.Create(Offset_Pos + sf::Vector2f(45, 3), 300, *evtd, sysp->P_System[id]->Name);
    title.SetStyle(ts);

    down.Create(Offset_Pos + sf::Vector2f(144, 322), sf::Vector2f(100, 50), ">", *evtd, sf::Color::Black, true);

    InitPosition();
    InitRadius();
    InitColor();

    InitMC();

    InitVelocity();
    InitAccelerationA();
    InitAccelerationB();
}

Object_Editor::~Object_Editor()
{
    //dtor
}

void Object_Editor::Draw(sf::RenderWindow& win, sf::View& view, float dt)
{
    title.Update();

    if(!title.isActive())
    {
        sysp->P_System[id]->Name = title.GetInput();
    }

    if(down.Draw(win) && !isShifting)
    {
        mode = 1 - mode;

        if(mode)
        {
            direction = sf::Vector2f(0.0f, 1.0f);
            isShifting = true;
        }
        else
        {
            direction = sf::Vector2f(0.0f,-1.0f);
            isShifting = true;
        }
    }

    if((abs(Moved.y) < 310.0f) && isShifting)
    {
        Speed += 100.0f * dt;

        sf::Vector2f Move = direction * dt * Speed;
        view.move(Move);
        Moved += Move;
    }
    else
    {
        if(abs(Moved.y) > 310.0f)
        {
            sf::FloatRect view_port = view.getViewport();

            view_port.top = (direction.y * (abs(Moved.y) - 310.0f))/float(win.getSize().y);

            view.move(sf::Vector2f(0.0f, view_port.top));
        }

        if(mode)
        {
            down.SetText(">");
        }
        else
        {
            down.SetText("<");
        }

        direction = sf::Vector2f();
        Moved = sf::Vector2f();
        isShifting = false;
        Speed = 50.0f;
    }

    title.Draw(win);

    DrawPosition(win);
    DrawRadius(win);
    DrawColor(win);

    DrawMC(win);

    DrawVelocity(win);
    DrawAccelerationB(win);
    DrawAccelerationA(win);

    down.Draw(win);
}

void Object_Editor::InitPosition()
{
    //Text
    Pos_Label.setPosition(Offset_Pos + sf::Vector2f(-45, 40));
    Pos_Label.setString("Position:");
    Pos_Label.scale(sf::Vector2f(0.75f, 0.75f));
    Pos_Label.setFillColor(sf::Color::Black);

    float w = Pos_Label.getGlobalBounds().width + Pos_Label.getGlobalBounds().left;

    x.setPosition(sf::Vector2f(w - 60.0f, 60));
    x.setString("X:");
    x.scale(sf::Vector2f(0.75f, 0.75f));
    x.setFillColor(sf::Color(0, 255, 0));

    w = x.getGlobalBounds().width + x.getGlobalBounds().left + 120;

    y.setPosition(sf::Vector2f(w + 10, 60));
    y.setString("Y:");
    y.scale(sf::Vector2f(0.75f, 0.75f));
    y.setFillColor(sf::Color(0, 255, 0));

    w = y.getGlobalBounds().width + y.getGlobalBounds().left + 120;

    z.setPosition(sf::Vector2f(w + 10, 60));
    z.setString("Z:");
    z.scale(sf::Vector2f(0.75f, 0.75f));
    z.setFillColor(sf::Color(0, 255, 0));

    // UI Elements
    UI::TextBox_Style ts;

    ts.isCentered = true;
    ts.Bold_Text = true;

    ts.Selected_Color = sf::Color(255, 255, 255, 192);
    ts.Default_Color = sf::Color(255, 255, 255, 128);
    ts.Scale = sf::Vector2f(0.75f, 0.75f);

    w = x.getGlobalBounds().left + x.getGlobalBounds().width;

    ts.Text_Color = sf::Color::Red;
    PositionX.Create(sf::Vector2f(w + 5.0f, 65), 140, *evtd, float_to_string(sysp->P_System[id]->Position.x), true);
    PositionX.SetStyle(ts);

    w = y.getGlobalBounds().left + y.getGlobalBounds().width;

    ts.Text_Color = sf::Color::Green;
    PositionY.Create(sf::Vector2f(w + 5.0f, 65), 140, *evtd, float_to_string(sysp->P_System[id]->Position.y), true);
    PositionY.SetStyle(ts);

    w = z.getGlobalBounds().left + z.getGlobalBounds().width;

    ts.Text_Color = sf::Color::Blue;
    PositionZ.Create(sf::Vector2f(w + 5.0f, 65), 140, *evtd, float_to_string(sysp->P_System[id]->Position.y), true);
    PositionZ.SetStyle(ts);
}

void Object_Editor::DrawPosition(sf::RenderWindow& win)
{
    PositionX.Update();
    PositionY.Update();
    PositionZ.Update();

    if(PositionX.isActive())
    {
        if((PositionX.GetInput() != "")  && (PositionX.GetInput() != "-"))
        {
            float val = std::stof(PositionX.GetInput());

            if(val > (-200.0f + sysp->P_System[id]->radius) && val < (200.0f - sysp->P_System[id]->radius))
            {
                sysp->P_System[id]->Position.x = val;
            }
            else
            {
                if(val < (-200.0f + sysp->P_System[id]->radius))
                {
                    PositionX.resetValue(float_to_string(-200.0f + sysp->P_System[id]->radius));
                    sysp->P_System[id]->Position.x = (-200.0f + sysp->P_System[id]->radius);
                }
                else if(val > (200.0f - sysp->P_System[id]->radius))
                {
                    PositionX.resetValue(float_to_string(200.0f - sysp->P_System[id]->radius));
                    sysp->P_System[id]->Position.x = (200.0f - sysp->P_System[id]->radius);
                }
            }
        }
    }
    else
    {
        PositionX.resetValue(float_to_string(sysp->P_System[id]->Position.x));
    }

    if(PositionY.isActive())
    {
        if((PositionY.GetInput() != "")  && (PositionY.GetInput() != "-"))
        {
            float val = std::stof(PositionY.GetInput());

            if(val > (-200.0f + sysp->P_System[id]->radius) && val < (200.0f - sysp->P_System[id]->radius))
            {
                sysp->P_System[id]->Position.y = val;
            }
            else
            {
                if(val < (-200.0f + sysp->P_System[id]->radius))
                {
                    PositionY.resetValue(float_to_string(-200.0f + sysp->P_System[id]->radius));
                    sysp->P_System[0]->Position.y = (-200.0f + sysp->P_System[id]->radius);
                }
                else if(val > (200.0f - sysp->P_System[id]->radius))
                {
                    PositionY.resetValue(float_to_string(200.0f - sysp->P_System[id]->radius));
                    sysp->P_System[id]->Position.y = (200.0f - sysp->P_System[id]->radius);
                }
            }
        }
    }
    else
    {
        PositionY.resetValue(float_to_string(sysp->P_System[id]->Position.y));
    }

    if(PositionZ.isActive())
    {
        if((PositionZ.GetInput() != "")  && (PositionZ.GetInput() != "-"))
        {
            float val = std::stof(PositionZ.GetInput());

            if(val > (-200.0f + sysp->P_System[id]->radius) && val < (200.0f - sysp->P_System[id]->radius))
            {
                sysp->P_System[id]->Position.z = val;
            }
            else
            {
                if(val < (-200.0f + sysp->P_System[id]->radius))
                {
                    PositionZ.resetValue(float_to_string(-200.0f + sysp->P_System[id]->radius));
                    sysp->P_System[0]->Position.z = (-200.0f + sysp->P_System[id]->radius);
                }
                else if(val > (200.0f - sysp->P_System[id]->radius))
                {
                    PositionZ.resetValue(float_to_string(200.0f - sysp->P_System[id]->radius));
                    sysp->P_System[id]->Position.z = (200.0f - sysp->P_System[id]->radius);
                }
            }
        }
    }
    else
    {
        PositionZ.resetValue(float_to_string(sysp->P_System[id]->Position.z));
    }

    win.draw(Pos_Label);

    x.setFillColor(sf::Color(0, 0, 0));
    win.draw(x);
    x.setFillColor(sf::Color(255, 0, 0, 192));
    win.draw(x);

    y.setFillColor(sf::Color(0, 0, 0));
    win.draw(y);
    y.setFillColor(sf::Color(0, 255, 0, 192));
    win.draw(y);

    z.setFillColor(sf::Color(0, 0, 0));
    win.draw(z);
    z.setFillColor(sf::Color(0, 0, 255, 192));
    win.draw(z);

    PositionX.Draw(win);
    PositionY.Draw(win);
    PositionZ.Draw(win);
}

void Object_Editor::InitRadius()
{
    //Text
    radius.setPosition(Offset_Pos + sf::Vector2f(10, 100));
    radius.setString("Radius:");
    radius.scale(sf::Vector2f(0.75f, 0.75f));
    radius.setFillColor(sf::Color::Black);

    float w = radius.getGlobalBounds().width + radius.getGlobalBounds().left;

    // UI Elements
    UI::TextBox_Style ts;

    ts.isCentered = true;
    ts.Selected_Color = sf::Color(255, 255, 255, 192);
    ts.Default_Color = sf::Color(255, 255, 255, 128);
    ts.Scale = sf::Vector2f(0.75f, 0.75f);

    TRadius.Create(sf::Vector2f(w + 5.0f, 105), 120, *evtd, float_to_string(sysp->P_System[id]->radius), true);
    TRadius.SetStyle(ts);
}

void Object_Editor::DrawRadius(sf::RenderWindow& win)
{
    TRadius.Update();

    if(!TRadius.isActive())
    {
        if(TRadius.GetInput() != "")
        {
            float r = std::stof(TRadius.GetInput());

            if(r > 0.0f)
            {
                sysp->P_System[id]->radius = r;
            }
            else
            {
                TRadius.resetValue(float_to_string(sysp->P_System[id]->radius));
            }
        }
        else
        {
            TRadius.resetValue(float_to_string(sysp->P_System[id]->radius));
        }
    }

    win.draw(radius);

    TRadius.Draw(win);
}

void Object_Editor::InitColor()
{
    //Text
    Color_Label.setPosition(Offset_Pos + sf::Vector2f(10, 130));
    Color_Label.setString("Color:");
    Color_Label.scale(sf::Vector2f(0.75f, 0.75f));
    Color_Label.setFillColor(sf::Color::Black);

    float w = Color_Label.getGlobalBounds().width + Color_Label.getGlobalBounds().left;

    pv.setString("Preview:");
    pv.scale(sf::Vector2f(0.75f, 0.75f));
    pv.setPosition(sf::Vector2f(w - pv.getGlobalBounds().width + 50.0f, 160));
    pv.setFillColor(sf::Color(255, 0, 0));

    Preview.setPosition(sf::Vector2f(w + 60.0f, 160));
    Preview.setSize(sf::Vector2f(pv.getGlobalBounds().height + 10.0f, pv.getGlobalBounds().height + 10.0f));
    Preview.setFillColor(sf::Color::Black);

    r.setString("Red:");
    r.scale(sf::Vector2f(0.75f, 0.75f));
    r.setPosition(sf::Vector2f(w - r.getGlobalBounds().width, 190));
    r.setFillColor(sf::Color(255, 0, 0));

    g.setString("Green:");
    g.scale(sf::Vector2f(0.75f, 0.75f));
    g.setPosition(sf::Vector2f(w - g.getGlobalBounds().width, 230));
    g.setFillColor(sf::Color(0, 255, 0));

    b.setString("Blue:");
    b.scale(sf::Vector2f(0.75f, 0.75f));
    b.setPosition(sf::Vector2f(w - b.getGlobalBounds().width, 270));
    b.setFillColor(sf::Color(0, 0, 255));

    //UI Element
    Red.Create(sf::Vector2f(w + 10.f, 200), 100, *evtd, sf::Color(255, 0, 0, 225));
    Red.Set_Limits(0, 255, sysp->P_System[id]->color.r);

    Green.Create(sf::Vector2f(w + 10.f, 240), 100, *evtd, sf::Color(0, 255, 0, 225));
    Green.Set_Limits(0, 255, sysp->P_System[id]->color.g);

    Blue.Create(sf::Vector2f(w + 10.f, 280), 100, *evtd, sf::Color(0, 0, 255, 225));
    Blue.Set_Limits(0, 255, sysp->P_System[id]->color.b);
}

void Object_Editor::DrawColor(sf::RenderWindow& win)
{
    win.draw(Color_Label);

    win.draw(pv);

    r.setFillColor(sf::Color::Black);
    win.draw(r);
    r.setFillColor(sf::Color(255, 0, 0, 192));
    win.draw(r);

    g.setFillColor(sf::Color::Black);
    win.draw(g);
    r.setFillColor(sf::Color(0, 255, 0, 192));
    win.draw(g);

    g.setFillColor(sf::Color::Black);
    win.draw(b);
    g.setFillColor(sf::Color(0, 0, 255, 192));
    win.draw(b);

    Preview.setFillColor(sf::Color(Red.Value, Green.Value, Blue.Value));
    win.draw(Preview);

    Red.Draw(win);
    Green.Draw(win);
    Blue.Draw(win);

    sysp->P_System[id]->color = sf::Color(Red.Value, Green.Value, Blue.Value);
}

void Object_Editor::InitMC()
{
    //Text
    sf::Vector2f Page_Offset = Offset_Pos + sf::Vector2f(-45, 340.0f);

    m_Label.setPosition(Page_Offset + sf::Vector2f(0.0f, 35));
    m_Label.setString("Mass:");
    m_Label.scale(sf::Vector2f(0.75f, 0.75f));
    m_Label.setFillColor(sf::Color::Black);

    c_Label.setPosition(Page_Offset + sf::Vector2f(0.0f, 65));
    c_Label.setString("Charge:");
    c_Label.scale(sf::Vector2f(0.75f, 0.75f));
    c_Label.setFillColor(sf::Color::Black);

    // UI
    UI::TextBox_Style ts;

    ts.Selected_Color = sf::Color(255, 255, 255, 192);
    ts.Default_Color = sf::Color(255, 255, 255, 128);
    ts.Scale = sf::Vector2f(0.75f, 0.75f);
    ts.Text_Color = sf::Color::Black;

    float w = m_Label.getGlobalBounds().left + m_Label.getGlobalBounds().width;

    Mass.Create(sf::Vector2f(w + 5.0f, 40) + sf::Vector2f(0, 340.0f), 140, *evtd, float_to_string(sysp->P_System[id]->Mass), true);
    Mass.SetStyle(ts);

    w = c_Label.getGlobalBounds().left + c_Label.getGlobalBounds().width;

    Charge.Create(sf::Vector2f(w + 5.0f, 70) + sf::Vector2f(0, 340.0f), 140, *evtd, float_to_string(sysp->P_System[id]->Charge), true);
    Charge.SetStyle(ts);
}

void Object_Editor::DrawMC(sf::RenderWindow& win)
{
    Mass.Update();
    Charge.Update();

    if(Mass.isActive())
    {
        if((Mass.GetInput() != "") && (Mass.GetInput() != "-"))
        {
            float val = std::stof(Mass.GetInput());

            if(val > 0.0f && val < 1000.0f)
            {
                sysp->P_System[id]->Mass = val;
            }
            else
            {
                if(val < 0.0f)
                {
                    Mass.resetValue(float_to_string(1.0f));
                    sysp->P_System[id]->Mass = 1.0f;
                }
                else if(val > 1000.0f)
                {
                    Mass.resetValue(float_to_string(1000.0f));
                    sysp->P_System[id]->Mass = 1000.0f;
                }
            }
        }
    }
    else
    {
        Mass.resetValue(float_to_string(sysp->P_System[id]->Mass));
    }

    if(Charge.isActive())
    {
        if((Charge.GetInput() != "") && (Charge.GetInput() != "-"))
        {
            float val = std::stof(Charge.GetInput());

            if(val >= -500.0f && val <= 500.0f)
            {
                sysp->P_System[id]->Charge = val;
            }
            else
            {
                if(val < -500.0f)
                {
                    Charge.resetValue(float_to_string(-500.0f));
                    sysp->P_System[id]->Charge = -500.0f;
                }
                else if(val > 500.0f)
                {
                    Charge.resetValue(float_to_string(500.0f));
                    sysp->P_System[id]->Charge = 500.0f;
                }
            }
        }
    }
    else
    {
        Charge.resetValue(float_to_string(sysp->P_System[id]->Charge));
    }

    win.draw(m_Label);
    win.draw(c_Label);

    Mass.Draw(win);
    Charge.Draw(win);
}

void Object_Editor::InitVelocity()
{
    //Text
    sf::Vector2f Page_Offset = Offset_Pos + sf::Vector2f(0, 340.0f);

    v_Label.setPosition(Page_Offset + sf::Vector2f(-45, 120));
    v_Label.setString("Velocity:");
    v_Label.scale(sf::Vector2f(0.75f, 0.75f));
    v_Label.setFillColor(sf::Color::Black);

    float w = v_Label.getGlobalBounds().width + v_Label.getGlobalBounds().left;

    vx.setPosition(sf::Vector2f(-10.0f, 150) + sf::Vector2f(Offset_Pos.x, 340.0f));
    vx.setString("X:");
    vx.scale(sf::Vector2f(0.75f, 0.75f));
    vx.setFillColor(sf::Color(0, 255, 0));

    w = vx.getGlobalBounds().width + vx.getGlobalBounds().left + 120;

    vy.setPosition(sf::Vector2f(w + 10, 150) + sf::Vector2f(0, 340.0f));
    vy.setString("Y:");
    vy.scale(sf::Vector2f(0.75f, 0.75f));
    vy.setFillColor(sf::Color(0, 255, 0));

    w = vy.getGlobalBounds().width + vy.getGlobalBounds().left + 120;

    vz.setPosition(sf::Vector2f(w + 10, 150) + sf::Vector2f(0, 340.0f));
    vz.setString("Z:");
    vz.scale(sf::Vector2f(0.75f, 0.75f));
    vz.setFillColor(sf::Color(0, 255, 0));

    // UI Elements
    UI::TextBox_Style ts;

    ts.isCentered = true;
    ts.Bold_Text = true;

    ts.Selected_Color = sf::Color(255, 255, 255, 192);
    ts.Default_Color = sf::Color(255, 255, 255, 128);
    ts.Scale = sf::Vector2f(0.75f, 0.75f);

    w = vx.getGlobalBounds().left + vx.getGlobalBounds().width;

    ts.Text_Color = sf::Color::Red;
    VelocityX.Create(sf::Vector2f(w + 5.0f, 155) + sf::Vector2f(0, 340.0f), 140, *evtd, float_to_string(sysp->P_System[id]->Velocity.x), true);
    VelocityX.SetStyle(ts);

    w = vy.getGlobalBounds().left + vy.getGlobalBounds().width;

    ts.Text_Color = sf::Color::Green;
    VelocityY.Create(sf::Vector2f(w + 5.0f, 155) + sf::Vector2f(0, 340.0f), 140, *evtd, float_to_string(sysp->P_System[id]->Velocity.y), true);
    VelocityY.SetStyle(ts);

    w = vz.getGlobalBounds().left + vz.getGlobalBounds().width;

    ts.Text_Color = sf::Color::Blue;
    VelocityZ.Create(sf::Vector2f(w + 5.0f, 155) + sf::Vector2f(0, 340.0f), 140, *evtd, float_to_string(sysp->P_System[id]->Velocity.z), true);
    VelocityZ.SetStyle(ts);
}

void Object_Editor::DrawVelocity(sf::RenderWindow& win)
{
    VelocityX.Update();
    VelocityY.Update();
    VelocityZ.Update();

    if(VelocityX.isActive())
    {
        if((VelocityX.GetInput() != "") && (VelocityX.GetInput() != "-"))
        {
            float val = std::stof(VelocityX.GetInput());

            if(val >= -200.0f && val <= 200.0f)
            {
                sysp->P_System[id]->u_Velocity.x = val;
            }
            else
            {
                if(val < -200.0f)
                {
                    VelocityX.resetValue(float_to_string(-200.0f));
                    sysp->P_System[id]->u_Velocity.x = -200.0f;
                }
                else if(val > 200.0f)
                {
                    VelocityX.resetValue(float_to_string(200.0f));
                    sysp->P_System[id]->u_Velocity.x = 200.0f;
                }
            }
        }
    }
    else
    {
        VelocityX.resetValue(float_to_string(sysp->P_System[id]->u_Velocity.x));
    }

    if(VelocityY.isActive())
    {
        if((VelocityY.GetInput() != "") && (VelocityY.GetInput() != "-"))
        {
            float val = std::stof(VelocityY.GetInput());

            if(val > -200.0f && val < 200.0f)
            {
                sysp->P_System[id]->u_Velocity.y = val;
            }
            else
            {
                if(val < -200.0f)
                {
                    VelocityY.resetValue(float_to_string(-200.0f));
                    sysp->P_System[0]->u_Velocity.y = -200.0f;
                }
                else if(val > 200.0f)
                {
                    VelocityY.resetValue(float_to_string(200.0f));
                    sysp->P_System[id]->u_Velocity.y = 200.0f;
                }
            }
        }
    }
    else
    {
        VelocityY.resetValue(float_to_string(sysp->P_System[id]->u_Velocity.y));
    }

    if(VelocityZ.isActive())
    {
        if((VelocityZ.GetInput() != "") && (VelocityZ.GetInput() != "-"))
        {
            float val = std::stof(VelocityZ.GetInput());

            if(val > -200.0f && val < 200.0f)
            {
                sysp->P_System[id]->u_Velocity.z = val;
            }
            else
            {
                if(val < -200.0f)
                {
                    VelocityZ.resetValue(float_to_string(-200.0f));
                    sysp->P_System[0]->u_Velocity.z = -200.0f;
                }
                else if(val > 200.0f)
                {
                    VelocityZ.resetValue(float_to_string(200.0f));
                    sysp->P_System[id]->u_Velocity.z = 200.0f;
                }
            }
        }
    }
    else
    {
        VelocityZ.resetValue(float_to_string(sysp->P_System[id]->u_Velocity.z));
    }

    win.draw(v_Label);

    vx.setFillColor(sf::Color(0, 0, 0));
    win.draw(vx);
    vx.setFillColor(sf::Color(255, 0, 0, 192));
    win.draw(vx);

    vy.setFillColor(sf::Color(0, 0, 0));
    win.draw(vy);
    vy.setFillColor(sf::Color(0, 255, 0, 192));
    win.draw(vy);

    vz.setFillColor(sf::Color(0, 0, 0));
    win.draw(vz);
    vz.setFillColor(sf::Color(0, 0, 255, 192));
    win.draw(vz);

    VelocityX.Draw(win);
    VelocityY.Draw(win);
    VelocityZ.Draw(win);
}

void Object_Editor::InitAccelerationA()
{
    //Text
    float Y = 190.0f;

    sf::Vector2f Page_Offset = Offset_Pos + sf::Vector2f(0, 340.0f);

    a_Label.setPosition(Page_Offset + sf::Vector2f(-45, Y));
    a_Label.setString("Acceleration:");
    a_Label.scale(sf::Vector2f(0.75f, 0.75f));
    a_Label.setFillColor(sf::Color::Black);

    float w = v_Label.getGlobalBounds().width + v_Label.getGlobalBounds().left;

    ax.setPosition(sf::Vector2f(-10.0f, Y + 25.0f) + sf::Vector2f(Offset_Pos.x, 340.0f));
    ax.setString("X:");
    ax.scale(sf::Vector2f(0.75f, 0.75f));
    ax.setFillColor(sf::Color(255, 0, 0));

    w = ax.getGlobalBounds().width + ax.getGlobalBounds().left + 120;

    ay.setPosition(sf::Vector2f(w + 10, Y + 25.0f) + sf::Vector2f(0, 340.0f));
    ay.setString("Y:");
    ay.scale(sf::Vector2f(0.75f, 0.75f));
    ay.setFillColor(sf::Color(0, 255, 0));

    w = ay.getGlobalBounds().width + ay.getGlobalBounds().left + 120;

    az.setPosition(sf::Vector2f(w + 10, Y + 25.0f) + sf::Vector2f(0, 340.0f));
    az.setString("Z:");
    az.scale(sf::Vector2f(0.75f, 0.75f));
    az.setFillColor(sf::Color(0, 0, 255));

    // Values
    w = ax.getGlobalBounds().left + ax.getGlobalBounds().width;

    avx.setPosition(sf::Vector2f(w + 5, Y + 25.0f) + sf::Vector2f(0, 340.0f));
    avx.scale(sf::Vector2f(0.75f, 0.75f));
    avx.setFillColor(sf::Color(255, 0, 0));

    w = ay.getGlobalBounds().left + ay.getGlobalBounds().width;

    avy.setPosition(sf::Vector2f(w + 5, Y + 25.0f) + sf::Vector2f(0, 340.0f));
    avy.scale(sf::Vector2f(0.75f, 0.75f));
    avy.setFillColor(sf::Color(0, 255, 0));

    w = az.getGlobalBounds().left + az.getGlobalBounds().width;

    avz.setPosition(sf::Vector2f(w + 5, Y + 25.0f) + sf::Vector2f(0, 340.0f));
    avz.scale(sf::Vector2f(0.75f, 0.75f));
    avz.setFillColor(sf::Color(0, 0, 255));

    Show_More.setSize(sf::Vector2f(20.0f, 20.0f));
    Show_More.setFillColor(sf::Color::Magenta);
    Show_More.setTexture(&Show_More_Tex);

    B.setString("Magnetic Acceleration:");
    B.scale(sf::Vector2f(0.5f, 0.5f));
    B.setFillColor(sf::Color(255, 255, 255, 225));

    G.setString("Gravity:");
    G.scale(sf::Vector2f(0.5f, 0.5f));
    G.setFillColor(sf::Color(255, 255, 255, 225));

    C.setString("Coulomb Acceleration:");
    C.scale(sf::Vector2f(0.5f, 0.5f));
    C.setFillColor(sf::Color(255, 255, 255, 225));

    //B
    Bx.scale(sf::Vector2f(0.5f, 0.5f));
    Bx.setFillColor(sf::Color(255, 0, 0, 255));

    By.scale(sf::Vector2f(0.5f, 0.5f));
    By.setFillColor(sf::Color(0, 255, 0, 255));

    Bz.scale(sf::Vector2f(0.5f, 0.5f));
    Bz.setFillColor(sf::Color(0, 0, 255, 255));

    //G
    Gx.scale(sf::Vector2f(0.5f, 0.5f));
    Gx.setFillColor(sf::Color(255, 0, 0, 255));

    Gy.scale(sf::Vector2f(0.5f, 0.5f));
    Gy.setFillColor(sf::Color(0, 255, 0, 255));

    Gz.scale(sf::Vector2f(0.5f, 0.5f));
    Gz.setFillColor(sf::Color(0, 0, 255, 255));

    //C
    Cx.scale(sf::Vector2f(0.5f, 0.5f));
    Cx.setFillColor(sf::Color(255, 0, 0, 255));

    Cy.scale(sf::Vector2f(0.5f, 0.5f));
    Cy.setFillColor(sf::Color(0, 255, 0, 255));

    Cz.scale(sf::Vector2f(0.5f, 0.5f));
    Cz.setFillColor(sf::Color(0, 0, 255, 255));

    // Values
    w = ax.getGlobalBounds().left + ax.getGlobalBounds().width;

    avx.setPosition(sf::Vector2f(w + 5, Y + 25.0f) + sf::Vector2f(0, 340.0f));
    avx.setFillColor(sf::Color(255, 0, 0));

    w = ay.getGlobalBounds().left + ay.getGlobalBounds().width;

    avy.setPosition(sf::Vector2f(w + 5, Y + 25.0f) + sf::Vector2f(0, 340.0f));
    avy.setFillColor(sf::Color(0, 255, 0));

    w = az.getGlobalBounds().left + az.getGlobalBounds().width;

    avz.setPosition(sf::Vector2f(w + 5, Y + 25.0f) + sf::Vector2f(0, 340.0f));
    avz.setFillColor(sf::Color(0, 0, 255));

    More_Info_Container.setFillColor(sf::Color(0, 0, 0, 225));
    More_Info_Container.setOutlineColor(sf::Color(255, 255, 255, 128));
    More_Info_Container.setOutlineThickness(2);
}

void Object_Editor::DrawAccelerationA(sf::RenderWindow& win)
{
    float Y = 210.0f;

    if(!evtd->WindowState.isFocused)
    {
        avx.setString(float_to_string(sysp->P_System[id]->Total_Accleration.x));
        avy.setString(float_to_string(sysp->P_System[id]->Total_Accleration.y));
        avz.setString(float_to_string(sysp->P_System[id]->Total_Accleration.z));

        Bx.setString(float_to_string(sysp->P_System[id]->Magnetic_Accleration.x) + ",");
        By.setString(float_to_string(sysp->P_System[id]->Magnetic_Accleration.y) + ",");
        Bz.setString(float_to_string(sysp->P_System[id]->Magnetic_Accleration.z));

        Gx.setString(float_to_string(sysp->P_System[id]->Gravity.x) + ",");
        Gy.setString(float_to_string(sysp->P_System[id]->Gravity.y) + ",");
        Gz.setString(float_to_string(sysp->P_System[id]->Gravity.z));

        Cx.setString(float_to_string(sysp->P_System[id]->Coulomb_Accleration.x) + ",");
        Cy.setString(float_to_string(sysp->P_System[id]->Coulomb_Accleration.y) + ",");
        Cz.setString(float_to_string(sysp->P_System[id]->Coulomb_Accleration.z));
    }

    win.draw(a_Label);

    ax.setFillColor(sf::Color(0, 0, 0));
    win.draw(ax);
    ax.setFillColor(sf::Color(255, 0, 0, 192));
    win.draw(ax);

    ay.setFillColor(sf::Color(0, 0, 0));
    win.draw(ay);
    ay.setFillColor(sf::Color(0, 255, 0, 192));
    win.draw(ay);

    az.setFillColor(sf::Color(0, 0, 0));
    win.draw(az);
    az.setFillColor(sf::Color(0, 0, 255, 192));
    win.draw(az);



    avx.setFillColor(sf::Color(0, 0, 0));
    win.draw(avx);
    avx.setFillColor(sf::Color(255, 0, 0, 192));
    win.draw(avx);

    avy.setFillColor(sf::Color(0, 0, 0));
    win.draw(avy);
    avy.setFillColor(sf::Color(0, 255, 0, 192));
    win.draw(avy);

    avz.setFillColor(sf::Color(0, 0, 0));
    win.draw(avz);
    avz.setFillColor(sf::Color(0, 0, 255, 192));
    win.draw(avz);

    float w = avz.getGlobalBounds().left + avz.getGlobalBounds().width;

    Show_More.setPosition(sf::Vector2f(w + 10.0f, Y + 10.0f) + sf::Vector2f(0, 340.0f));

    w = More_Info_Container.getGlobalBounds().left;

    B.setPosition(sf::Vector2f(w + 5.0f, Y + 40.0f) + sf::Vector2f(0, 340.0f));
    G.setPosition(sf::Vector2f(w + 5.0f, Y + 60.0f) + sf::Vector2f(0, 340.0f));
    C.setPosition(sf::Vector2f(w + 5.0f, Y + 80.0f) + sf::Vector2f(0, 340.0f));

    // Values B
    w = B.getGlobalBounds().left + B.getGlobalBounds().width;

    Bx.setPosition(sf::Vector2f(w + 5, Y + 40.0f) + sf::Vector2f(0, 340.0f));

    w = Bx.getGlobalBounds().left + Bx.getGlobalBounds().width;

    By.setPosition(sf::Vector2f(w + 5, Y + 40.0f) + sf::Vector2f(0, 340.0f));

    w = By.getGlobalBounds().left + By.getGlobalBounds().width;

    Bz.setPosition(sf::Vector2f(w + 5, Y + 40.0f) + sf::Vector2f(0, 340.0f));

    // Values G
    w = G.getGlobalBounds().left + G.getGlobalBounds().width;

    Gx.setPosition(sf::Vector2f(w + 5, Y + 60.0f) + sf::Vector2f(0, 340.0f));

    w = Gx.getGlobalBounds().left + Gx.getGlobalBounds().width;

    Gy.setPosition(sf::Vector2f(w + 5, Y + 60.0f) + sf::Vector2f(0, 340.0f));

    w = Gy.getGlobalBounds().left + Gy.getGlobalBounds().width;

    Gz.setPosition(sf::Vector2f(w + 5, Y + 60.0f) + sf::Vector2f(0, 340.0f));

    // Values C
    w = C.getGlobalBounds().left + C.getGlobalBounds().width;

    Cx.setPosition(sf::Vector2f(w + 5, Y + 80.0f) + sf::Vector2f(0, 340.0f));

    w = Cx.getGlobalBounds().left + Cx.getGlobalBounds().width;

    Cy.setPosition(sf::Vector2f(w + 5, Y + 80.0f) + sf::Vector2f(0, 340.0f));

    w = Cy.getGlobalBounds().left + Cy.getGlobalBounds().width;

    Cz.setPosition(sf::Vector2f(w + 5, Y + 80.0f) + sf::Vector2f(0, 340.0f));

    float SizeB = Bz.getGlobalBounds().width + By.getGlobalBounds().width + Bx.getGlobalBounds().width + B.getGlobalBounds().width + 15.0f;
    float SizeG = Gz.getGlobalBounds().width + Gy.getGlobalBounds().width + Gx.getGlobalBounds().width + G.getGlobalBounds().width + 15.0f;
    float SizeC = Cz.getGlobalBounds().width + Cy.getGlobalBounds().width + Cx.getGlobalBounds().width + C.getGlobalBounds().width + 15.0f;

    float Size = std::max(std::max(SizeB, SizeG), SizeC);

    More_Info_Container.setSize(sf::Vector2f(Size + 10.0f, 80.0f));
    More_Info_Container.setOrigin(sf::Vector2f(Size + 10.0f, 0.0f));

    w = avz.getGlobalBounds().left + avz.getGlobalBounds().width;

    More_Info_Container.setPosition(sf::Vector2f(w + 30.0f, Y + 35.0f) + sf::Vector2f(0, 340.0f));

    win.draw(Show_More);

    sf::FloatRect fr = Show_More.getGlobalBounds();

    if(fr.contains(evtd->MouseState.MousePos))
    {
        win.draw(More_Info_Container);
        win.draw(B);
        win.draw(G);
        win.draw(C);

        win.draw(Bx); win.draw(By); win.draw(Bz);
        win.draw(Gx); win.draw(Gy); win.draw(Gz);
        win.draw(Cx); win.draw(Cy); win.draw(Cz);
    }
}

void Object_Editor::InitAccelerationB()
{
    //Text
    float Y = 260.0f;

    sf::Vector2f Page_Offset = Offset_Pos + sf::Vector2f(0, 340.0f);

    ab_Label.setPosition(Page_Offset + sf::Vector2f(-45, Y));
    ab_Label.setString("Apply Constant Acceleration:");
    ab_Label.scale(sf::Vector2f(0.75f, 0.75f));
    ab_Label.setFillColor(sf::Color::Black);

    float w = ab_Label.getGlobalBounds().width + ab_Label.getGlobalBounds().left;

    abx.setPosition(sf::Vector2f(-10.0f, Y + 30.0f) + sf::Vector2f(Offset_Pos.x, 340.0f));
    abx.setString("X:");
    abx.scale(sf::Vector2f(0.75f, 0.75f));
    abx.setFillColor(sf::Color(0, 255, 0));

    w = abx.getGlobalBounds().width + abx.getGlobalBounds().left + 120;

    aby.setPosition(sf::Vector2f(w + 10, Y + 30.0f) + sf::Vector2f(0, 340.0f));
    aby.setString("Y:");
    aby.scale(sf::Vector2f(0.75f, 0.75f));
    aby.setFillColor(sf::Color(0, 255, 0));

    w = aby.getGlobalBounds().width + aby.getGlobalBounds().left + 120;

    abz.setPosition(sf::Vector2f(w + 10, Y + 30.0f) + sf::Vector2f(0, 340.0f));
    abz.setString("Z:");
    abz.scale(sf::Vector2f(0.75f, 0.75f));
    abz.setFillColor(sf::Color(0, 255, 0));

    // UI Elements
    UI::TextBox_Style ts;

    ts.isCentered = true;
    ts.Bold_Text = true;

    ts.Selected_Color = sf::Color(255, 255, 255, 192);
    ts.Default_Color = sf::Color(255, 255, 255, 128);
    ts.Scale = sf::Vector2f(0.75f, 0.75f);

    w = abx.getGlobalBounds().left + abx.getGlobalBounds().width;

    ts.Text_Color = sf::Color::Red;
    AccelerationX.Create(sf::Vector2f(w + 5.0f, Y + 35) + sf::Vector2f(0, 340.0f), 140, *evtd, float_to_string(sysp->P_System[id]->Accleration.x), true);
    AccelerationX.SetStyle(ts);

    w = aby.getGlobalBounds().left + aby.getGlobalBounds().width;

    ts.Text_Color = sf::Color::Green;
    AccelerationY.Create(sf::Vector2f(w + 5.0f, Y + 35) + sf::Vector2f(0, 340.0f), 140, *evtd, float_to_string(sysp->P_System[id]->Accleration.y), true);
    AccelerationY.SetStyle(ts);

    w = abz.getGlobalBounds().left + abz.getGlobalBounds().width;

    ts.Text_Color = sf::Color::Blue;
    AccelerationZ.Create(sf::Vector2f(w + 5.0f, Y + 35) + sf::Vector2f(0, 340.0f), 140, *evtd, float_to_string(sysp->P_System[id]->Accleration.z), true);
    AccelerationZ.SetStyle(ts);
}

void Object_Editor::DrawAccelerationB(sf::RenderWindow& win)
{
    AccelerationX.Update();
    AccelerationY.Update();
    AccelerationZ.Update();

    if(AccelerationX.isActive())
    {
        if((AccelerationX.GetInput() != "") && (AccelerationX.GetInput() != "-"))
        {
            float val = std::stof(AccelerationX.GetInput());

            if(val >= -200.0f && val <= 200.0f)
            {
                sysp->P_System[id]->Accleration.x = val;
            }
            else
            {
                if(val < -200.0f)
                {
                    AccelerationX.resetValue(float_to_string(-200.0f));
                    sysp->P_System[id]->Accleration.x = -200.0f;
                }
                else if(val > 200.0f)
                {
                    AccelerationX.resetValue(float_to_string(200.0f));
                    sysp->P_System[id]->Accleration.x = 200.0f;
                }
            }
        }
    }
    else
    {
        AccelerationX.resetValue(float_to_string(sysp->P_System[id]->Accleration.x));
    }

    if(AccelerationY.isActive())
    {
        if((AccelerationY.GetInput() != "") && (AccelerationY.GetInput() != "-"))
        {
            float val = std::stof(AccelerationY.GetInput());

            if(val > -200.0f && val < 200.0f)
            {
                sysp->P_System[id]->Accleration.y = val;
            }
            else
            {
                if(val < -200.0f)
                {
                    AccelerationY.resetValue(float_to_string(-200.0f));
                    sysp->P_System[0]->Accleration.y = -200.0f;
                }
                else if(val > 200.0f)
                {
                    AccelerationY.resetValue(float_to_string(200.0f));
                    sysp->P_System[id]->Accleration.y = 200.0f;
                }
            }
        }
    }
    else
    {
        AccelerationY.resetValue(float_to_string(sysp->P_System[id]->Accleration.y));
    }

    if(AccelerationZ.isActive())
    {
        if((AccelerationZ.GetInput() != "") && (AccelerationZ.GetInput() != "-"))
        {
            float val = std::stof(AccelerationZ.GetInput());

            if(val > -200.0f && val < 200.0f)
            {
                sysp->P_System[id]->Accleration.z = val;
            }
            else
            {
                if(val < -200.0f)
                {
                    AccelerationZ.resetValue(float_to_string(-200.0f));
                    sysp->P_System[0]->Accleration.z = -200.0f;
                }
                else if(val > 200.0f)
                {
                    AccelerationZ.resetValue(float_to_string(200.0f));
                    sysp->P_System[id]->Accleration.z = 200.0f;
                }
            }
        }
    }
    else
    {
        AccelerationZ.resetValue(float_to_string(sysp->P_System[id]->Accleration.z));
    }

    win.draw(ab_Label);

    abx.setFillColor(sf::Color(0, 0, 0));
    win.draw(abx);
    abx.setFillColor(sf::Color(255, 0, 0, 192));
    win.draw(abx);

    aby.setFillColor(sf::Color(0, 0, 0));
    win.draw(aby);
    aby.setFillColor(sf::Color(0, 255, 0, 192));
    win.draw(aby);

    abz.setFillColor(sf::Color(0, 0, 0));
    win.draw(abz);
    abz.setFillColor(sf::Color(0, 0, 255, 192));
    win.draw(abz);

    AccelerationX.Draw(win);
    AccelerationY.Draw(win);
    AccelerationZ.Draw(win);
}

#include "InputStream.h"
#include <iomanip>

UI::InputStream::InputStream(UI::EventData& e)
{
    this->e = &e;
}

UI::InputStream::~InputStream()
{
    //dtor
}

void UI::InputStream::ListenInput()
{
    Listen = true;
}

void UI::InputStream::__Update_Stream()
{
    if(!Listen || StringStream.size() >= Stream_Limit) return;

    UI::EventData ed = *e;
    UI::KeyboardData kd = ed.KeyboardState;

    if(int(kd.Key))
    {
        StringStream += kd.Key;
    }

    flush();
}

std::string UI::InputStream::GetString()
{
    Listen = false;

    std::string ss = StringStream;

    StringStream = std::string();

    return ss;
}

void UI::InputStream::SetLimit(int s_Limit)
{
    Stream_Limit = s_Limit;
}

void UI::InputStream::SetEventHandler(UI::EventData& e)
{
    this->e = &e;
}

void UI::InputStream::flush()
{
    e->KeyboardState.Key = char(0);
}

char UI::InputStream::Listen_Charecter()
{
    char a = e->KeyboardState.Key;

    flush();

    return a;
}

#include "ErrorStream.h"

UI::ErrorStream::ErrorStream()
{
    //ctor
}

UI::ErrorStream::~ErrorStream()
{
    //dtor
}

void UI::ErrorStream::NewError(std::string Error_Name, std::string Error_Discription, bool Kill_Program)
{
    MessageBox( NULL, Error_Discription.c_str(), Error_Name.c_str(), MB_OK | MB_ICONERROR);

    if(Kill_Program) raise(SIGBREAK);
}

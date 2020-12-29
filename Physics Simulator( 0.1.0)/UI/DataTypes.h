#ifndef DATATYPES_H
#define DATATYPES_H

#include <iostream>
#include <sstream>

namespace UI
{
    class DataTypes
    {
        public:
            static std::string ConvertToString(int i)
            {
                return std::string(std::to_string(i));
            }

            static std::string ConvertToString(float i, int Digits = 2)
            {
                std::string Float(std::to_string(i));

                std::string Ans;

                for(int i = 0; i < Float.size(); i++)
                {
                    Ans += std::string({Float[i], '\0'});

                    if(Float[i] == '.')
                    {
                        for(int j = 0; j <= Digits; j++)
                        {
                            Ans += std::string({Float[j + i], '\0'});
                        }
                        return Ans;
                    }
                }

                return Ans;
            }
    };
}

#endif // DATATYPES_H

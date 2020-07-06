#include <iostream>
#include "to_string.h"

int main()
{
    std::vector<std::string> s(10, "abc");
    std::cout << to_string(s) << std::endl;
    TO_STRING::CONSOLE_WIDTH = 10;
    std::cout << to_string(s) << std::endl;
    return 0;
}
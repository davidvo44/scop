#pragma once

#include <iostream>
//#include <GLFW/glfw3.h>

#define TRY(expression) \
try \
{ \
    expression; \
} \
catch(const std::exception& e) \
{ \
    std::cerr << e.what() << std::endl; \
}

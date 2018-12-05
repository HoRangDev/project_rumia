#include "Core/EngineDefines.hpp"
#include "Math/Vector2.hpp"

#include <iostream>

int main()
{
   rumia::Vector2 vec{ 0.3f, 20.f };
   std::cout << vec.xx << ", " << vec.yy << std::endl;
   return 0;
}
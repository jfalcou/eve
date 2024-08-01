// revision 0
#include <eve/module/core.hpp>
#include <iostream>

int main()
{
  eve::wide pi = {1, 3, 7, 15, 31, 63, 127, 255};

  std::cout << "<- pi                       = " << pi << '\n';
  std::cout << "-> bit_flip(pi, 1)          = " << eve::bit_flip(pi, 1) << '\n';
  std::cout << "-> bit_flip(pi, 2)          = " << eve::bit_flip(pi, 2) << '\n';
  std::cout << "-> bit_flip(pi, 3)          = " << eve::bit_flip(pi, 3) << '\n';
  std::cout << "-> bit_flip(pi, 4)          = " << eve::bit_flip(pi, 4) << '\n';
  std::cout << "-> bit_flip(pi, 8)          = " << eve::bit_flip(pi, 8) << '\n';
  std::cout << "-> bit_flip[pi > 15](pi, 1) = " << eve::bit_flip[pi > 15](pi, 1) << '\n';
  std::cout << "-> bit_flip[pi > 15](pi, 2) = " << eve::bit_flip[pi > 15](pi, 2) << '\n';
  std::cout << "-> bit_flip[pi > 15](pi, 3) = " << eve::bit_flip[pi > 15](pi, 3) << '\n';
  std::cout << "-> bit_flip[pi > 15](pi, 4) = " << eve::bit_flip[pi > 15](pi, 4) << '\n';
  std::cout << "-> bit_flip[pi > 15](pi, 8) = " << eve::bit_flip[pi > 15](pi, 8) << '\n';

}

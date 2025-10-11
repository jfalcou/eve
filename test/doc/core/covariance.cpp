// revision 0
#include <eve/module/core.hpp>
#include <iostream>
#include <iomanip>
#include <tts/tts.hpp>

int main()
{
  kumi::tuple x{4.0f, 3.0f, 2.0f, 1.0f};
  kumi::tuple y{1.0f, 2.0f, 3.0f, 4.0f};
  std::cout << eve::covariance(x, x) <<  std::endl;
  std::cout << eve::covariance(x, y) <<  std::endl;
  std::cout << eve::covariance(y, x) <<  std::endl;

}

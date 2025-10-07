// revision 0
#include <eve/module/core.hpp>
#include <iostream>
#include <iomanip>
#include <tts/tts.hpp>

int main()
{
  std::cout << eve::welford_covariance(1.0f, 2.0f, -3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 48.0f, 9.0f, 10.0f).covariance << std::endl;
  std::cout << eve::covariance(1.0f, 2.0f, -3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 48.0f, 9.0f, 10.0f) << std::endl;
}

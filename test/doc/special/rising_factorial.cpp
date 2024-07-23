// revision 1
#include <eve/module/special.hpp>
#include <iostream>

eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);});

int main()
{
  eve::wide n = {1, 2, -3, 7};
  eve::wide p = {1.0f,  1.5f, 2.0f, 2.5f};

  std::cout << "<- n                                     = " << n << "\n";
  std::cout << "<- p                                     = " << p << "\n";

  std::cout << "-> rising_factorial(n, p)                = " << eve::rising_factorial(n, p) << "\n";
  std::cout << "-> rising_factorial[ignore_last(2)](n, p)= " << eve::rising_factorial[eve::ignore_last(2)](n, p) << "\n";
  std::cout << "-> rising_factorial[wf != -2.0f](n, p)   = " << eve::rising_factorial[wf != -2.0f](n, p) << "\n";
  std::cout << "-> rising_factorial[raw](n, p)           = " << eve::rising_factorial[eve::raw](n, p) << "\n";
  std::cout << "-> rising_factorial[pedantic](n, p)      = " << eve::rising_factorial[eve::pedantic](n, p) << "\n";
}

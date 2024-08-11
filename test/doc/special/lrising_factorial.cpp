// revision 1
#include <eve/module/special.hpp>
#include <iostream>

int main()
{
  eve::wide n = {1, 2, -3, 7};
  eve::wide p = {1.0f,  1.5f, 2.0f, 2.5f};

  std::cout << "<- n                                      = " << n << "\n";
  std::cout << "<- p                                      = " << p << "\n";

  std::cout << "-> lrising_factorial(n, p)                = " << eve::lrising_factorial(n, p) << "\n";
  std::cout << "-> lrising_factorial[ignore_last(2)](n, p)= " << eve::lrising_factorial[eve::ignore_last(2)](n, p) << "\n";
  std::cout << "-> lrising_factorial[n != 2](n, p)        = " << eve::lrising_factorial[n != 2](n, p) << "\n";
  std::cout << "-> lrising_factorial[raw2](n, p)           = " << eve::lrising_factorial[eve::raw2](n, p) << "\n";
  std::cout << "-> lrising_factorial[pedantic](n, p)      = " << eve::lrising_factorial[eve::pedantic](n, p) << "\n";
}

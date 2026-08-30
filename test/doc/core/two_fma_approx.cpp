// revision 0
#include <eve/module/core.hpp>
#include <iostream>
#include <iomanip>

int main()
{
  eve::wide a = {1.0, 2.0, 3.0, 1.0e8};
  eve::wide x = {0.1, 0.2, 0.3, 1.0e-8};
  eve::wide y = {1.0e-20, 1.0, 2.0, 1.0};

  std::cout << std::setprecision(20);
  std::cout << "<- a                        = " << a << "\n";
  std::cout << "<- x                        = " << x << "\n";
  std::cout << "<- y                        = " << y << "\n";

  auto [f, e1] = eve::two_fma_approx(a, x, y);
  std::cout << "-> f  (the fma itself)      = " << f  << "\n";
  std::cout << "-> e1 (the rounding error)  = " << e1 << "\n";
}

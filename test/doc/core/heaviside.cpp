#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  eve::wide x = {2.0, -3.0, 0.1, 4.0};
  eve::wide s = {3.0, -4.0, -10.0, 0.0};

  std::cout << " <- x                     = " << x << '\n';
  std::cout << " <- s                     = " << s << '\n';
  std::cout << " -> heaviside(x)          = " << eve::heaviside(x) << '\n';
  std::cout << " -> heaviside(x, s)       = " << eve::heaviside(x, s) << '\n';
  std::cout << " -> heaviside[x > -2](x)  = " << eve::heaviside[x > -2](x, s) << '\n';
}

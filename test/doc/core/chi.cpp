#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  eve::wide x = {2.0, -3.0, 0.1, 4.0};
  eve::wide lo = {3.0, -4.0, -10.0, 0.0};
  eve::wide hi = {4.0, -1.0, 0.0, 5.0};

  auto belongs =  [](auto x){return x > 3.0 || x == 2.0; };

  std::cout << " <- x                       = " << x << '\n';
  std::cout << " <- lo                      = " << lo << '\n';
  std::cout << " <- hi                      = " << hi << '\n';
  std::cout << " -> chi(x, belongs)         = " << eve::chi(x, belongs) << '\n';
  std::cout << " -> chi(x, lo, hi)          = " << eve::chi(x, lo, hi) << '\n';
  std::cout << " -> chi[x > -2](x, lo, hi)  = " << eve::chi[x > -2](x, lo, hi) << '\n';
}

#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using w_t = eve::wide<std::int16_t, eve::fixed<4>>;
  w_t pi = {3, 2, 3, 32700}, qi = {4, 1, -1, 100};

  std::cout << "---- simd" << '\n'
            << " <- pi                      = " << pi << '\n'
            << " <- qi                      = " << qi << '\n'
            << " -> saturated(mul)((pi, qi) = " << eve::saturated(eve::mul)(pi, qi) << '\n';
  return 0;
}

#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using w_t = eve::wide<std::int16_t, eve::fixed<4>>;
  w_t pi = {3, 2, -32700, 32700}, qi = {4, 1, -100, 100};

  std::cout << "---- simd" << '\n'
            << " <- pi                   = " << pi << '\n'
            << " <- qi                   = " << qi << '\n'
            << " -> add[pi < qi](pi, qi) = " << eve::add[pi < qi](pi, qi) << '\n';
  return 0;
}

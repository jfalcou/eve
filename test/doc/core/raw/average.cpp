#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <vector>
#include <iostream>

int main()
{
  using w_t = eve::wide<float, eve::fixed<4>>;
  w_t pi = {3, 2, 3, 3},
      qi = {4, 1, 1, eve::valmax(eve::as<float>())},
      ri = {4, 1, 1, eve::valmax(eve::as<float>())};

  std::cout << "---- simd" << '\n'
            << " <- pi                       = " << pi << '\n'
            << " <- qi                       = " << qi << '\n'
            << " <- ri                       = " << ri << '\n'
            << " -> raw(average)(pi, qi, ri) = " << eve::raw(eve::average)(pi, qi, ri) << '\n'
            << " -> average(pi, qi, ri)      = " << eve::average(pi, qi, ri) << '\n';

  return 0;
}

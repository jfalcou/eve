#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using w_t = eve::wide<std::int16_t, eve::fixed<4>>;
  w_t pi = {3, 2, 3, 32700}, qi = {4, 2, 2, 101};

  std::cout << "---- simd" << '\n'
            << " <- pi =          " << pi << '\n'
            << " <- qi =          " << qi << '\n'
            << " <- toward_zero(rem)(pi, qi)   = " << eve::toward_zero(eve::rem)(pi, qi) << '\n'
            << " -> upward(rem)(pi, qi)   = " << eve::downward(eve::rem)(pi, qi) << '\n'
            << " -> downward(rem)(pi, qi) = " << eve::upward(eve::rem)(pi, qi) << '\n'
            << " -> to_nearest(rem)(pi, qi) = " << eve::to_nearest(eve::rem)(pi, qi) << '\n'
            << " -> pi % qi     = " << pi % qi << '\n';

  return 0;
}

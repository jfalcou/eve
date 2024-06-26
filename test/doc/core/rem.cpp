#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

consteval auto constexpr_rem(auto a, auto b) { return eve::rem(a, b); }

int main()
{
  using w_t = eve::wide<std::int16_t, eve::fixed<4>>;
  w_t pi = {3, 2, 3, 32700}, qi = {4, 2, 1, 101},  ri = {4, 2, 0, 101};

  std::cout << "---- simd" << '\n'
            << " <- pi                        = " << pi << '\n'
            << " <- qi                        = " << qi << '\n'
            << " <- ri                        = " << ri << '\n'
            << " -> rem(pi, qi)               = " << eve::rem(pi, qi) << '\n'
            << " -> rem[toward_zero](pi, qi)  = " << eve::rem[eve::toward_zero](pi, qi) << '\n'
            << " -> rem[downward](pi, qi)     = " << eve::rem[eve::downward](pi, qi) << '\n'
            << " -> rem[upward](pi, qi)       = " << eve::rem[eve::upward](pi, qi) << '\n'
            << " -> rem[toward_zero](pi, qi)  = " << eve::rem[eve::to_nearest](pi, qi) << '\n'
//            << " -> rem[ri!= 0](pi, ri)       = " << eve::rem[ri!= 0](pi, ri) << '\n'
            << " -> pi % qi                   = " << pi % qi << '\n';

  std::int16_t xi  = 32700,  yi = 101;

  std::cout << "---- scalar" << '\n'
            << " xi             = " << xi << '\n'
            << " yi             = " << yi << '\n'
            << " -> rem(xi, yi) = " << eve::rem(xi, yi) << '\n'
            << " -> xi % yi     = " << xi % yi << '\n';

//  std::cout << "-> constexpr_rem(1.0f,2.0f) = " << constexpr_rem(1.0f,2.0f) << std::endl;

  return 0;
}

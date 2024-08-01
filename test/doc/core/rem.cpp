// revision 1
#include <eve/module/core.hpp>
#include <iostream>

int main()
{
  using w_t = eve::wide<std::int16_t, eve::fixed<4>>;
  w_t pi = {3, 2, 3, 32700}, qi = {4, 2, 1, 101},  ri = {4, 2, 0, 101};

  std::cout << " <- pi                        = " << pi << '\n'
            << " <- qi                        = " << qi << '\n'
            << " <- ri                        = " << ri << '\n'
            << " -> rem(pi, qi)               = " << eve::rem(pi, qi) << '\n'
            << " -> rem[toward_zero](pi, qi)  = " << eve::rem[eve::toward_zero](pi, qi) << '\n'
            << " -> rem[downward](pi, qi)     = " << eve::rem[eve::downward](pi, qi) << '\n'
            << " -> rem[upward](pi, qi)       = " << eve::rem[eve::upward](pi, qi) << '\n'
            << " -> rem[toward_zero](pi, qi)  = " << eve::rem[eve::to_nearest](pi, qi) << '\n'
            << " -> pi % qi                   = " << pi % qi << '\n';

}

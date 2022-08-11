#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using w_t = eve::wide<std::float, eve::fixed<8>>;
  w_t pf = {3.2, 2.5, 3.5, 3.6, 0.3, -2.4, -3.5, -3-2};

  std::cout << "---- simd" << '\n'
            << " <- pi                     = " << pf << '\n'
            << " <- toward_zero(round)(pf) = " << eve::toward_zero(eve::round)(pf) << '\n'
            << " -> upward(round)(pf)      = " << eve::downward(eve::round)(pf) << '\n'
            << " -> downward(round)(pf)    = " << eve::upward(eve::round)(pf) << '\n'
            << " -> to_nearest(round)(pf)  = " << eve::to_nearest(eve::round)(pf) << '\n';
  return 0;
}

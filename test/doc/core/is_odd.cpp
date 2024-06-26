#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;

consteval auto constexpr_is_odd(auto a) { return eve::is_odd(a); }

int main()
{
  wide_ft pf = {0.0f, 1.0f, -1.5f, -2.0f};

  std::cout << "---- simd" << '\n'
            << "<- pf                 = " << pf << '\n'
            << "-> is_odd(pf)         = " << eve::is_odd(pf) << '\n'
            << "-> is_odd[pf > 0](pf) = " << eve::is_odd[pf > 0](pf) << '\n';

  float xf = 1.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf         = " << xf << '\n'
            << "-> is_odd(xf) = " << eve::is_odd(xf) << '\n';

//  std::cout << "-> constexpr_is_odd(1.0f) = " << constexpr_is_odd(1.0f) << std::endl;

  return 0;
}

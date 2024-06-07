#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;

consteval auto constexpr_rec(auto a) { return eve::rec(a); }

int main()
{
  wide_ft pf = {0.0f, 1.0f, 2.0f, 10.0f, 200.0f, 1000.0f,
               eve::inf(eve::as<float>()), eve::nan(eve::as<float>())};

  std::cout << "---- simd" << '\n'
            << "<- pf              = " << pf << '\n'
            << "-> rec(pf)         = " << eve::rec(pf) << '\n'
            << "-> rec[pf > 3](pf) = " << eve::rec[pf > 1](pf) << '\n';

  float xf = 1.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf      = " << xf << '\n'
            << "-> rec(xf) = " << eve::rec(xf) << '\n';

//  std::cout << "-> constexpr_rec(1.0f) = " << constexpr_rec(1.0f) << std::endl;

  return 0;
}

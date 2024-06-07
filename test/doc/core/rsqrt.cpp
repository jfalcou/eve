#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;

consteval auto constexpr_rsqrt(auto a) { return eve::rsqrt(a); }

int main()
{
  wide_ft pf = {1.0f, 0.5f, -3.0f, eve::inf(eve::as<float>())};

  std::cout << "---- simd" << '\n'
            << "<- pf               = " << pf << '\n'
            << "-> rsqrt(pf)        = " << eve::rsqrt(pf) << '\n'
            << "-> rsqrt[raw](pf)   = " << eve::rsqrt[eve::raw2](pf) << '\n'
            << "-> rsqrt[pf > 0](pf)= " << eve::rsqrt[pf > 0](pf) << '\n';

  float xf = 32.768f;

  std::cout << "---- scalar" << '\n'
            << "<- xf               = " << xf << '\n'
            << "-> rsqrt(xf)        = " << eve::rsqrt(xf) << '\n';


//  std::cout << "-> constexpr_rsqrt(1.0f) = " << constexpr_rsqrt(1.0f) << std::endl;

  return 0;
}

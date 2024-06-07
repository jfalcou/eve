#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;

consteval auto constexpr_is_nltz(auto a) { return eve::is_nltz(a); }

int main()
{
  wide_ft pf = {0.0f, 1.0f, -1.0f, -0.0f};

  std::cout << "---- simd" << '\n'
            << "<- pf                   = " << pf << '\n'
            << "-> is_nltz(pf)          = " << eve::is_nltz(pf) << '\n'
            << "-> is_nltz[pf<-0.5](pf) = " << eve::is_nltz[pf < -0.5](pf) << '\n';

  float xf = 1.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf          = " << xf << '\n'
            << "-> is_nltz(xf) = " << eve::is_nltz(xf) << '\n';

  std::cout << "-> constexpr_is_nltz(1.0f) = " << constexpr_is_nltz(1.0f) << std::endl;

  return 0;
}

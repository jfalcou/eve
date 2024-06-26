#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;

consteval auto constexpr_is_ngtz(auto a) { return eve::is_ngtz(a); }

int main()
{
  wide_ft pf = {0.0f, 1.0f, -1.0f, -0.0f};

  std::cout << "---- simd" << '\n'
            << "<- pf                  = " << pf << '\n'
            << "-> is_ngtz(pf)         = " << eve::is_ngtz(pf) << '\n'
           << "-> is_ngtz[pf<-0.5](pf) = " << eve::is_ngtz[pf<-0.5](pf) << '\n';

  float xf = 1.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf          = " << xf << '\n'
            << "-> is_ngtz(xf) = " << eve::is_ngtz(xf) << '\n';

  std::cout << "-> constexpr_is_ngtz(1.0f) = " << constexpr_is_ngtz(1.0f) << std::endl;

  return 0;
}

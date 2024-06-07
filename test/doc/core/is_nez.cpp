#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;

consteval auto constexpr_is_nez(auto a) { return eve::is_nez(a); }

int main()
{
  wide_ft pf = {0.0f, 1.0f, -1.0f, -0.0f};

  std::cout << "---- simd" << '\n'
            << "<- pf                  = " << pf << '\n'
            << "-> is_nez(pf)          = " << eve::is_nez(pf) << '\n'
            << "-> is_nez[pf<-0.5](pf) = " << eve::is_nez[pf <  -0.5](pf) << '\n';

  float xf = 1.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf         = " << xf << '\n'
            << "-> is_nez(xf) = " << eve::is_nez(xf) << '\n';

  std::cout << "-> constexpr_is_nez(1.0f) = " << constexpr_is_nez(1.0f) << std::endl;

  return 0;
}

#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;

consteval auto constexpr_is_ngez(auto a) { return eve::is_ngez(a); }

int main()

{
  wide_ft pf = {0.0f, 1.0f, -1.0f, -0.0f};

  std::cout << "---- simd" << '\n'
            << "<- pf                  =" << pf << '\n'
            << "-> is_ngez(pf)         = " << eve::is_ngez(pf) << '\n'
            << "-> is_gez[pf<-0.5](pf) = " << eve::is_ngez[pf <  -0.5](pf) << '\n';

  float xf = 1.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf          = " << xf << '\n'
            << "-> is_ngez(xf) = " << eve::is_ngez(xf) << '\n';

  std::cout << "-> constexpr_is_ngez(1.0f) = " << constexpr_is_ngez(1.0f) << std::endl;

  return 0;
}

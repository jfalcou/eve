#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;

consteval auto constexpr_conj(auto a) { return eve::conj(a); }

int main()
{
  wide_ft pf = {-1.0f, 2.0f, -3.0f, -32768.0f};

  std::cout << "---- simd" << '\n'
            << "<- pf                   = " << pf << '\n'
            << "-> conj(pf)             = " << eve::conj(pf) << '\n';

  float        xf = -32768.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf                   = " << xf << '\n'
            << "-> conj(xf)             = " << eve::conj(xf) << '\n';

  std::cout << "-> constexpr_conj(1.0f) = " << constexpr_conj(1.0f) << std::endl;

  return 0;
}

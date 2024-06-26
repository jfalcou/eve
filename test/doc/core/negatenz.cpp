#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;

consteval auto constexpr_negatenz(auto a, auto b) { return eve::negatenz(a, b); }

int main()
{
  wide_ft pf = {0.0f, -0.0f, 0.0f, -2.0f, 2.0f, -2.0f, 2.0f, -2.0f};

  wide_ft qf = {4.0f, 4.0f, -4.0f, -4.0, 0.0f, 0.0f, -0.0f,  -0.0f};

  std::cout << "---- simd" << '\n'
            << "<- pf                         = " << pf << '\n'
            << "<- qf                         = " << qf << '\n'
            << "-> negatenz(pf, qf)           = " << eve::negatenz(pf, qf) << '\n'
            << "-> negatenz[pf < qf](pf, qf)  = " << eve::negatenz[pf < qf](pf, qf) << '\n';

  float xf = 4.0f;
  float yf = -0.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf               = " << xf << '\n'
            << "<- yf               = " << yf << '\n'
            << "-> negatenz(xf, yf) = " << eve::negatenz(xf, yf) << '\n';

  std::cout << "-> constexpr_negatenz(1.0f,2.0f) = " << constexpr_negatenz(1.0f,2.0f) << std::endl;

  return 0;
}

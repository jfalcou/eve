#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_it = eve::wide<float, eve::fixed<4>>;

consteval auto constexpr_fdim(auto a, auto b) { return eve::fdim(a, b); }

int main()
{
  wide_it pf = {0, 1, -1, -eve::valmax(eve::as<float>())};
  wide_it qf = {1, -1, 0, eve::valmax(eve::as<float>())};

  std::cout << "---- simd" << '\n'
            << "<- pf                     = " << pf << '\n'
            << "<- qf                     = " << qf << '\n'
            << "-> fdim(pf, qf)           = " << eve::fdim(pf, qf) << '\n'
            << "-> fdim[pf > qf](pf, qf)  = " << eve::fdim[pf > qf](pf, qf) << '\n';

  float xf = -eve::valmax(eve::as<float>());
  float yf = eve::valmax(eve::as<float>());

  std::cout << "---- scalar" << '\n'
            << "<- xf           = " << xf << '\n'
            << "<- yf           = " << yf << '\n'
            << "-> fdim(xf, yf) = " << eve::fdim(xf, yf) << '\n'
            << '\n';

  std::cout << "-> constexpr_fdim(1.0f,2.0f) = " << constexpr_fdim(1.0f,2.0f) << std::endl;

  return 0;
}

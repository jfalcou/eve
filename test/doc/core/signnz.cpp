#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;
using wide_it = eve::wide<std::int16_t, eve::fixed<4>>;

consteval auto constexpr_signnz(auto a) { return eve::signnz(a); }

int main()
{
  wide_ft pf = {-0.0f, 2.0f, -3.0f, -32768.0f,
                 0.0f, -2.0f, 3.0f, 32768.0f};
  wide_it pi = { 0, 2, -3, -32768};

  std::cout << "---- simd" << '\n'
            << "<- pf                   = " << pf << '\n'
            << "-> signnz(pf)           = " << eve::signnz(pf) << '\n'
            << "-> signnz(pedantic2](pf) = " << eve::signnz[eve::pedantic2](pf) << '\n'
            << "-> signnz[abs(pf)<2](pf)= " << eve::signnz[eve::abs(pf)<2](pf) << '\n'
            << "<- pi                   = " << pi << '\n'
            << "-> signnz(pi)           = " << eve::signnz(pi) << '\n';

  float        xf = -327.68f;
  std::int16_t xi = -328;

  std::cout << "---- scalar" << '\n'
            << "<- xf         = " << xf << '\n'
            << "-> signnz(xf) = " << eve::signnz(xf) << '\n'
            << "<- xi         = " << xi << '\n'
            << "-> signnz(xi) = " << eve::signnz(xi) << '\n';

  std::cout << "-> constexpr_signnz(1.0f) = " << constexpr_signnz(1.0f) << std::endl;

  return 0;
}

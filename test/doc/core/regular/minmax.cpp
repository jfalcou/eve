#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;
using eve::pedantic;

int main()
{
  wide_ft pf = {0.0f, 1.0f, -1.0f, -2.0f, 2.0f,
                eve::inf(eve::as<float>()), eve::minf(eve::as<float>()), eve::nan(eve::as<float>())};
  wide_ft qf = {4.0f, 1.0f, -1.0f,  0.0f, eve::nan(eve::as<float>()),
                -0.0f, eve::nan(eve::as<float>()), -2.0f};


  std::cout << "---- simd" << '\n'
            << "<- pf                     = " << pf << '\n'
            << "<- qf                     = " << qf << '\n'
            << "-> minmax(pf, qf)            = " << eve::minmax(pf, qf) << '\n';

  float xf = 1.0f;
  float yf = eve::nan(eve::as<float>());

  std::cout << "---- scalar" << '\n'
            << "<- xf                     = " << xf << '\n'
            << "<- yf                     = " << yf << '\n'
            << "-> minmax(xf, yf) =          = " << eve::minmax(xf, yf) << '\n';

  auto k = kumi::tuple{pf, qf, pf+qf, 1};
  std::cout << "---- multi parameters" << '\n'
            << " -> minmax(k)                                = " << eve::minmax(k) << '\n'
            << " -> minmax(kumi::tuple{pf, pf, 1})           = " << eve::minmax( kumi::tuple{pf, qf, 1}) << '\n'
            << " -> minmax(kumi::tuple{1, pf, pf})           = " << eve::minmax( kumi::tuple{1, pf, qf}) << '\n'
            << " -> minmax(kumi::tuple{pf, 1.0f)             = " << eve::minmax( kumi::tuple{pf, 1.0f}) << '\n'
            << " -> minmax(kumi::tuple{1.0f, pf)             = " << eve::minmax( kumi::tuple{1.0f, pf}) << '\n';

  return 0;
}

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
            << "-> min(pf, qf)            = " << eve::min(pf, qf) << '\n';

  float xf = 1.0f;
  float yf = eve::nan(eve::as<float>());

  std::cout << "---- scalar" << '\n'
            << "<- xf                     = " << xf << '\n'
            << "<- yf                     = " << yf << '\n'
            << "-> min(xf, yf) =          = " << eve::min(xf, yf) << '\n';
  auto k = kumi::tuple{pf, qf, pf+qf, 1};
  std::cout << "---- multi parameters" << '\n'
            << " -> min(k)                                = " << eve::min(k) << '\n'
            << " -> min(kumi::tuple{pf, pf, 1})           = " << eve::min( kumi::tuple{pf, qf, 1}) << '\n'
            << " -> min(kumi::tuple{1, pf, pf})           = " << eve::min( kumi::tuple{1, pf, qf}) << '\n'
            << " -> numeric(min(kumi::tuple{1.0f, pf, qf) = " << eve::numeric(eve::min)( kumi::tuple{1.0f, pf,qf}) << '\n'
            << " -> min(kumi::tuple{pf, 1.0f)             = " << eve::min( kumi::tuple{pf, 1.0f}) << '\n'
            << " -> min(kumi::tuple{1.0f, pf)             = " << eve::min( kumi::tuple{1.0f, pf}) << '\n'
            << " -> numeric(min(kumi::tuple{1.0f, pf)     = " << eve::numeric(eve::min)( kumi::tuple{1.0f, pf}) << '\n';
  return 0;
}

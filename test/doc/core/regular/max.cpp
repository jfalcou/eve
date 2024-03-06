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
            << "<- pf                         = " << pf << '\n'
            << "<- qf                         = " << qf << '\n'
            << "-> max(pf, qf)                = " << eve::max(pf, qf) << '\n'
            << "-> max[eve::numeric](pf, qf)  = " << eve::max[eve::numeric2](pf, qf) << '\n'
            << "-> max[eve::pedantic](pf, qf) = " << eve::max[eve::pedantic](pf, qf) << '\n'
            << "-> max[eve::pedantic](qf, pf) = " << eve::max[eve::pedantic](qf, pf) << '\n';

  float xf = 1.0f;
  float yf = eve::nan(eve::as<float>());

  std::cout << "---- scalar" << '\n'
            << "<- xf                     = " << xf << '\n'
            << "<- yf                     = " << yf << '\n'
            << "-> max(xf, yf) =          = " << eve::max(xf, yf) << '\n';

//   auto k = kumi::tuple{pf, qf, pf+qf, 1.0f};
//   std::cout << "---- multi parameters" << '\n'
//             << " -> max(k)                                = " << eve::max(k) << '\n'
//             << " -> max(kumi::tuple{pf, pf, 1.0f})        = " << eve::max( kumi::tuple{pf, qf, 1.0f}) << '\n'
//             << " -> max(kumi::tuple{1.0f, pf, pf})        = " << eve::max( kumi::tuple{1.0f, pf, qf}) << '\n'
//             << " -> max[numeric](kumi::tuple{1.0f, pf, qf)= " << eve::max[eve::numeric2]( kumi::tuple{1.0f, pf,qf}) << '\n'
//             << " -> max(kumi::tuple{pf, 1.0f)             = " << eve::max( kumi::tuple{pf, 1.0f}) << '\n'
//             << " -> max(kumi::tuple{1.0f, pf)             = " << eve::max( kumi::tuple{1.0f, pf}) << '\n'
//             << " -> max[numeric](kumi::tuple{1.0f, pf)    = " << eve::max[eve::numeric2]( kumi::tuple{1.0f, pf}) << '\n'
//             << " -> max(eve::is_greater)(pf, qf)          = " << eve::max(eve::is_greater)(pf, qf) << '\n';
  return 0;
}

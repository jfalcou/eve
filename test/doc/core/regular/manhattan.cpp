#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_ft pf = {-1.0f, 2.0f, -3.0f, -32768.0f};
  wide_ft qf = {-4, 3, -2, -12};

  std::cout << "---- simd" << '\n'
            << "<- pf                     = " << pf << '\n'
            << "<- qf                     = " << qf << '\n'
            << "-> eve::manhattan(pf, qf) = " << eve::manhattan(pf, qf) << '\n';

  float        xf = -32768.0f;
  float        yf = 2.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf                     = " << xf << '\n'
            << "<- yf                     = " << yf << '\n'
            << "-> eve::manhattan(xf, yf) = " << eve::manhattan(xf, yf) << '\n';

  auto k = kumi::tuple{pf, qf, pf+qf, 1.0f};
  std::cout << "---- multi parameters" << '\n'
            << " -> manhattan(k)                                = " << eve::manhattan(k) << '\n'
            << " -> manhattan(kumi::tuple{pf, pf, 1.0f})        = " << eve::manhattan( kumi::tuple{pf, qf, 1}) << '\n'
            << " -> manhattan(kumi::tuple{1, pf, pf})           = " << eve::manhattan( kumi::tuple{1, pf, qf}) << '\n'
            << " -> manhattan(kumi::tuple{pf, 1.0f)             = " << eve::manhattan( kumi::tuple{pf, 1.0f}) << '\n'
            << " -> manhattan(kumi::tuple{1.0f, pf)             = " << eve::manhattan( kumi::tuple{1.0f, pf}) << '\n';
  return 0;
}

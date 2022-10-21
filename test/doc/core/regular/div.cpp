#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using wf_t = eve::wide<float, eve::fixed<4>>;
  wf_t pf = {3, 2, 3, 32700}, qf = {4, 1, 1, 100};

  std::cout << "---- simd" << '\n'
            << " <- pf                    = " << pf << '\n'
            << " <- qf                    = " << qf << '\n'
            << " -> div(pf, qf)           = " << eve::div(pf, qf) << '\n'
            << " -> pf / qf               = " << pf / qf << '\n';

  std::int16_t xi = -32768, yi = -1;

  std::cout << "---- scalar" << '\n'
            << " xi                        = " << xi << '\n'
            << " yi                        = " << yi << '\n'
            << " -> div(xi, yi)            = " << eve::div(xi, yi) << '\n'
            << " -> xi / yi                = " << xi / yi << '\n' // C++ promotion to int
            << " -> std::int16_t( xi / yi) = "<< std::int16_t( xi / yi) << '\n';


  auto k = kumi::tuple{pf, pf, pf, 1};
  std::cout << "---- multi parameters" << '\n'
            << " -> div(pf, k)                    = " << eve::div(pf, k)             << '\n'
            << " -> div(1, k)                     = " << eve::div(1, k)            << '\n'
            << " -> div(k)                        = " << eve::div(k)               << '\n'
            << " -> div(kumi::tuple{})            = " << eve::div( kumi::tuple{})  << '\n'
            << " -> div(kumi::tuple{pf, pf})      = " << eve::div( kumi::tuple{pf, pf})  << '\n'
            << " -> div(kumi::tuple{pf, 1.0f)     = " << eve::div( kumi::tuple{pf, 1.0f})  << '\n'
            << " -> div(kumi::tuple{1.0f, pf)     = " << eve::div( kumi::tuple{1.0f, pf})  << '\n';

  return 0;
}

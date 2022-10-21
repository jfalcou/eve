#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using w_t = eve::wide<std::int16_t, eve::fixed<4>>;
  w_t pi = {3, 2, 3, 32700}, qi = {4, 1, -1, 100};
  using wf_t = eve::wide<float, eve::fixed<4>>;
  wf_t pf = {3.5, 2, 3, 32700}, qf = {4, -1.3, 1, 100};

  std::cout << "---- simd" << '\n'
            << " <- pi                      = " << pi << '\n'
            << " <- qi                      = " << qi << '\n'
            << " -> mul(pi, qi)             = " << eve::mul(pi, qi) << '\n'
            << " -> pi * qi                 = " << pi * qi << '\n'
            << " -> saturated(mul)((pi, qi) = " << eve::saturated(eve::mul)(pi, qi) << '\n'
            << " <- pf                      = " << pf << '\n'
            << " <- qf                      = " << qf << '\n'
            << " -> mul(pf, qf)             = " << eve::mul(pf, qf) << '\n'
            << " -> pf * qf                 = " << pf * qf << '\n';

  std::int16_t xi = 100, yi = 32700;

  std::cout << "---- scalar" << '\n'
            << " xi             = " << xi << '\n'
            << " yi             = " << yi << '\n'
            << " -> mul(xi, yi) = " << eve::mul(xi, yi) << '\n'
            << " -> xi * yi     = " << xi * yi << '\n'; // C++ promotion

  auto k = kumi::tuple{pf, pf, pf, 1};
  std::cout << "---- multi parameters" << '\n'
            << " -> mul(pi,pi,pi,1)               = " << eve::mul(pi, pi, pi, 1) << '\n'
            << " -> mul(pf, k)                    = " << eve::mul(pf, k)             << '\n'
            << " -> mul(1, k)                     = " << eve::mul(1, k)            << '\n'
            << " -> mul(k)                        = " << eve::mul(k)               << '\n'
            << " -> mul(kumi::tuple{})            = " << eve::mul( kumi::tuple{})  << '\n'
            << " -> mul(kumi::tuple{pf, pf})      = " << eve::mul( kumi::tuple{pf, pf})  << '\n'
            << " -> mul(kumi::tuple{pf, 1.0f)     = " << eve::mul( kumi::tuple{pf, 1.0f})  << '\n'
            << " -> mul(kumi::tuple{1.0f, pf)     = " << eve::mul( kumi::tuple{1.0f, pf})  << '\n'
            << " -> saturated(mul)(pi,12,pi,pi)   = " << eve::saturated(eve::mul)(pi, 12, pi,pi) << '\n';
  return 0;
}

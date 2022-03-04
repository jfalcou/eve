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
            << " -> pf * qf                 = " << pf * qf << '\n'
            << " -> diff_1st(mul)(pf, qf)   = " <<  eve::diff_1st(eve::mul)(pf, qf) << '\n'
            << " -> diff_2nd(mul)(pf, qf)   = " <<  eve::diff_2nd(eve::mul)(pf, qf) << '\n';

  std::int16_t xi = 100, yi = 32700;

  std::cout << "---- scalar" << '\n'
            << " xi             = " << xi << '\n'
            << " yi             = " << yi << '\n'
            << " -> mul(xi, yi) = " << eve::mul(xi, yi) << '\n'
            << " -> xi * yi     = " << xi * yi << '\n'; // C++ promotion
  return 0;
}

#include <eve/module/math.hpp>

#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using w_t = eve::wide<float, eve::fixed<4>>;
  w_t pf = {3, 2, 3, 3}, qf = {4, 1, 1, ~0};

  std::cout << "---- simd" << '\n'
            << " <- pf                             = " << pf << '\n'
            << " <- qf                             = " << qf << '\n'
            << " -> logspace_add(pf, qf)           = " << eve::logspace_add(pf, qf) << '\n'
            << " -> diff_1st(logspace_add)(pf, qf) = " << eve::diff_1st(eve::logspace_add)(pf, qf) << '\n'
            << " -> diff_2nd(logspace_add)(pf, qf) = " << eve::diff_2nd(eve::logspace_add)(pf, qf) << '\n';

  float xi = 3, yi = 4;

  std::cout << "---- scalar" << '\n'
            << " xi                      = " << xi << '\n'
            << " yi                      = " << yi << '\n'
            << " -> logspace_add(xi, yi) = " << eve::logspace_add(xi, yi) << '\n';
  return 0;
}

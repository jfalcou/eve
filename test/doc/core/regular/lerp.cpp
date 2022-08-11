#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using wf_t = eve::wide<double, eve::fixed<4>>;
  wf_t pf = {3, 2.5, -32.7, 1327.43}, qf = {4.2, 1.5, -100.834, 10.02}, tf = {0, 0.1, -3, 1.0};

  std::cout << "---- simd" << '\n'
            << " <- pf               = " << pf << '\n'
            << " <- qf               = " << qf << '\n'
            << " <- tf               = " << tf << '\n'
            << " -> lerp(pf, qf, tf) = " << eve::add(pf, qf, tf) << '\n';

  double x = 10000, y = 32700, t = 0.5;

  std::cout << "---- scalar" << '\n'
            << " <- x             = " << x << '\n'
            << " <- y             = " << y << '\n'
            << " <- t             = " << t  << '\n'
            << " -> lerp(x, y, t) = " << eve::add(x, y, t) << '\n';
  return 0;
}

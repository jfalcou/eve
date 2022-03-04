#include <eve/module/math.hpp>

#include <eve/wide.hpp>
#include <vector>
#include <iostream>

int main()
{
  using w_t = eve::wide<double, eve::fixed<4>>;
  w_t pi = {3, 2, 3, -3}, qi = {4, 2, 1, -100};

  std::cout << "---- simd" << '\n'
            << " <- pi               = " << pi << '\n'
            << " <- qi               = " << qi << '\n'
            << " -> geommean(pi, qi) = " << eve::geommean(pi, qi) << '\n';

  float xi = 3, yi = 4;

  std::cout << "---- scalar" << '\n'
            << " xi                  = " << xi << '\n'
            << " yi                  = " << yi << '\n'
            << " -> geommean(xi, yi) = " << eve::geommean(xi, yi) << '\n';

  w_t pf = {3, 1, -3, -10}, qf = {4, 1, 1, 15};;
  std::cout << "---- multi" << '\n'
            << " <- pf                             = " << pf << '\n'
            << " <- qf                             = " << qf << '\n'
            << " -> geommean(1.0f, qf, pf, 32.0f)  = " << eve::geommean(1.0f, qf, pf, 32.0f) <<  '\n'
            << " -> geommean(1.0f, qf, pf, 32.0f)  = " << eve::geommean(1.0f, qf, pf, 32.0f) <<  '\n'
            << " -> geommean(-1.0f, qf, pf)        = " << eve::geommean(-1.0f, qf, pf) <<  '\n';

  return 0;
}

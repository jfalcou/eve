#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <vector>
#include <iostream>

int main()
{
  using w_t = eve::wide<std::uint32_t, eve::fixed<4>>;
  w_t pi = {3, 2, 3, 3};
  w_t qi = {4, 1, 1, eve::valmax(eve::as<float>())};
  w_t ri = {4, 1, 1, eve::valmax(eve::as<float>())};

  std::cout << "---- simd" << '\n'
            << " <- pi                       = " << pi << '\n'
            << " <- qi                       = " << qi << '\n'
            << " -> average(pi, qi)          = " << eve::average(pi, qi) << '\n';
//            << " -> average(pi, qi, ri)      = " << eve::average(pi, qi, ri) << '\n';

  std::uint32_t xi = 3, yi = 4;

  std::cout << "---- scalar" << '\n'
            << " xi                 = " << xi << '\n'
            << " yi                 = " << yi << '\n'
            << " -> average(xi, yi) = " << eve::average(xi, yi) << '\n';

  using w_ft = eve::wide<float, eve::fixed<4>>;
  w_ft pf = {3, 4, 3, 10}, qf = {4, 1, 1, 15};;
  std::cout << "---- multi" << '\n'
            << " <- pf                               = " << pf << '\n'
            << " <- qf                               = " << qf << '\n'
            << " -> average(pf, 0.0f, qf, pf, 11.0f) = " << eve::average(pf, 0.0f, qf, pf, 11.0f) <<  '\n'
            << " -> raw(average)(pi, qi, ri)         = " << eve::average[eve::raw](pf, 0.0f, pf, qf, 11.0f) << '\n';

  std::cout << "---- multi parameters" << '\n';
  return 0;
}

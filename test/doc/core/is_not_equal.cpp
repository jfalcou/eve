#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_ft pf = {0.0f, 1.0f, -1.0f, -2.0f};
  wide_ft qf = {1.0f, -1.0f, -1.0f, -2.0f};

  std::cout << "---- simd" << '\n'
            << "<- pf                   = " << pf << '\n'
            << "<- qf                   = " << qf << '\n'
            << "-> is_not_equal(pf, qf) = " << eve::is_not_equal(pf, qf) << '\n';

  pf += 3*eve::eps(eve::as<float>());

  std::cout << "---- simd" << '\n'
            << "<- pf                                     = " << pf << '\n'
            << "<- qf                                     = " << qf << '\n'
            << "-> is_not_equal)(pf, qf)                  = " << eve::is_not_equal(pf, qf) << '\n'
            << "-> definitely(is_not_equal)(pf, qf)       = " << eve::definitely(eve::is_not_equal)(pf, qf) << '\n'
            << "-> definitely(is_not_equal)(pf, qf, 2)    = " << eve::definitely(eve::is_not_equal)(pf, qf, 2) << '\n'
            << "-> definitely(is_not_equal)(pf, qf, 2.0f) = " << eve::definitely(eve::is_not_equal)(pf, qf, 2.0f) << '\n';

  float xf = 1.0f;
  float yf = 2.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf                   = " << xf << '\n'
            << "<- yf                   = " << yf << '\n'
            << "-> is_not_equal(xf, yf) = " << eve::is_not_equal(xf, yf) << '\n';
  return 0;
}

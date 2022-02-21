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
            << "<- pf                     = " << pf << '\n'
            << "<- qf                     = " << qf << '\n'
            << "-> min(pf, qf)            = " << eve::min(pf, qf) << '\n'
            << "-> pedantic(min)(pf, qf)  = " << eve::pedantic(eve::min)(pf, qf) << '\n'
            << "-> numeric(min)(pf, qf)   = " << eve::numeric(eve::min)(pf, qf) << '\n'
            << "-> diff_1st(min)(pf, qf)  = " <<  eve::diff_1st(eve::min)(pf, qf) <<  '\n'
            << "-> diff_2nd(min)(pf, qf)  = " <<  eve::diff_2nd(eve::min)(pf, qf) <<  '\n';

  float xf = 1.0f;
  float yf = eve::nan(eve::as<float>());

  std::cout << "---- scalar" << '\n'
            << "<- xf                     = " << xf << '\n'
            << "<- yf                     = " << yf << '\n'
            << "-> min(xf, yf) =          = " << eve::min(xf, yf) << '\n'
            << "-> pedantic(min)(xf, yf)  = " << eve::pedantic(eve::min)(xf, yf) << '\n'
            << "-> numeric(min)(xf, yf)   = " << eve::numeric(eve::min)(xf, yf) << '\n';
  return 0;
}

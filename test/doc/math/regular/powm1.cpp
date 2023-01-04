#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;

int main()
{
  wide_ft pf = {0.0f, 1.1f, 1.10f, -2.3f, 2.0f,
                eve::inf(eve::as<float>()), eve::inf(eve::as<float>()), eve::nan(eve::as<float>())};
  wide_ft qf = {4.0f, 1.0f, -1.0f,  0.0f,  -0.5f,
                eve::nan(eve::as<float>()), -2.0f,  eve::nan(eve::as<float>())};

  std::cout << "---- simd" << '\n'
            << "<- pf                      = " << pf << '\n'
            << "<- qf                      = " << qf << '\n'
            << "-> powm1(pf, qf)           = " << eve::powm1(pf, qf) << '\n'
            
            ;

  float xf = 4.0f;
  float yf = -1.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf            = " << xf << '\n'
            << "<- yf            = " << yf << '\n'
            << "-> powm1(xf, yf) = " << eve::powm1(xf, yf) << '\n';
  return 0;
}
